#include "Clove/Graphics/OpenGL/GLCommandBuffer.hpp"

#include "Clove/Graphics/OpenGL/Resources/GLBuffer.hpp"
#include "Clove/Graphics/OpenGL/Resources/GLTexture.hpp"
#include "Clove/Graphics/OpenGL/GLPipelineObject.hpp"
#include "Clove/Graphics/OpenGL/GLRenderTarget.hpp"
#include "Clove/Graphics/OpenGL/GLShader.hpp"
#include "Clove/Graphics/OpenGL/GLSurface.hpp"

#include <glad/glad.h>

namespace clv::gfx::ogl{
	GLCommandBuffer::GLCommandBuffer(const std::shared_ptr<RenderTarget>& renderTarget){
		glRenderTarget = std::static_pointer_cast<GLRenderTarget>(renderTarget);
	}

	GLCommandBuffer::GLCommandBuffer(Surface& surface){
		glRenderTarget = std::static_pointer_cast<GLRenderTarget>(surface.getRenderTarget());
	}

	GLCommandBuffer::GLCommandBuffer(GLCommandBuffer&& other) noexcept = default;

	GLCommandBuffer& GLCommandBuffer::operator=(GLCommandBuffer&& other) noexcept = default;

	GLCommandBuffer::~GLCommandBuffer() = default;

	void GLCommandBuffer::beginEncoding(){
		glRenderTarget->lock();

		const auto beginCommand = [glRenderTarget = glRenderTarget.get()](){
			glBindFramebuffer(GL_FRAMEBUFFER, glRenderTarget->getGLFrameBufferID());
			glRenderTarget->clear();
		};

		commands.emplace_back(beginCommand);
	}

	void GLCommandBuffer::bindIndexBuffer(const Buffer& buffer){
		const auto bindIBCommand = [&buffer](){
			const auto& glbuffer = static_cast<const GLBuffer&>(buffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glbuffer.getBufferID());
		};

		commands.emplace_back(bindIBCommand);
	}

	void GLCommandBuffer::bindVertexBuffer(const Buffer& buffer, const uint32_t stride){
		const auto bindVBCommand = [&buffer, stride](){
			const auto& glbuffer = static_cast<const GLBuffer&>(buffer);
			glBindVertexBuffer(0, glbuffer.getBufferID(), 0, stride);
		};

		commands.emplace_back(bindVBCommand);
	}

	void GLCommandBuffer::bindShaderResourceBuffer(const Buffer& buffer, const ShaderStage shaderType, const uint32_t bindingPoint){
		const auto bindSRBCommand = [&buffer, shaderType, bindingPoint](){
			const auto& glbuffer = static_cast<const GLBuffer&>(buffer);
			glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, glbuffer.getBufferID());
		};

		commands.emplace_back(bindSRBCommand);
	}

	void GLCommandBuffer::bindPipelineObject(const PipelineObject& pipelineObject){
		const auto bindPOCommand = [&pipelineObject](){
			const auto& glPipelineObject = static_cast<const GLPipelineObject&>(pipelineObject);
			glBindVertexArray(glPipelineObject.getGLVertexArrayID());
			glUseProgram(glPipelineObject.getGLPorgramID());

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if(glPipelineObject.isBlendEnabled()){
				glEnable(GL_BLEND);
			} else{
				glDisable(GL_BLEND);
			}

			glFrontFace(glPipelineObject.isFrontFaceCounterClockwise() ? GL_CCW : GL_CW);
			glCullFace(glPipelineObject.getCullFace() == CullFace::Back ? GL_BACK : GL_FRONT);
			glEnable(GL_CULL_FACE);
		};

		commands.emplace_back(bindPOCommand);
	}

	void GLCommandBuffer::bindTexture(const Texture* texture, const uint32_t bindingPoint){
		const auto bindTextureCommand = [texture, bindingPoint](){
			if(const auto* glTexture = static_cast<const GLTexture*>(texture)){
				glBindTextureUnit(bindingPoint, glTexture->getTextureID());
			} else{
				glBindTextureUnit(bindingPoint, 0);
			}
		};

		commands.emplace_back(bindTextureCommand);
	}

	void GLCommandBuffer::setViewport(const Viewport& viewport){
		const auto setVPCommand = [&viewport](){
			glViewport(static_cast<GLint>(viewport.x), static_cast<GLint>(viewport.y), static_cast<GLsizei>(viewport.width), static_cast<GLsizei>(viewport.height));
		};

		commands.emplace_back(setVPCommand);
	}

	void GLCommandBuffer::setDepthEnabled(bool enabled){
		const auto setDECommand = [enabled](){
			glDepthFunc(GL_LESS);

			if(enabled){
				glEnable(GL_DEPTH_TEST);
			} else{
				glDisable(GL_DEPTH_TEST);
			}
		};

		commands.emplace_back(setDECommand);
	}

	void GLCommandBuffer::drawIndexed(const uint32_t count){
		const auto drawCommand = [count](){
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
		};

		commands.emplace_back(drawCommand);
	}

	void GLCommandBuffer::endEncoding(){
		for(auto& command : commands){
			command();
		}

		commands.clear();
		glRenderTarget->unlock();
	}
}
