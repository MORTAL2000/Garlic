#include "clvpch.hpp"
#include "GL4FrameBuffer.hpp"

#include "Graphics/OpenGL-4/Bindables/GL4Texture.hpp"

#include <glad/glad.h>

namespace clv::gfx{
	GL4FrameBuffer::GL4FrameBuffer(){
		glGenFramebuffers(1, &renderID);
	}

	GL4FrameBuffer::GL4FrameBuffer(GL4FrameBuffer&& other) noexcept = default;

	GL4FrameBuffer& GL4FrameBuffer::operator=(GL4FrameBuffer&& other) noexcept = default;

	GL4FrameBuffer::~GL4FrameBuffer(){
		glDeleteFramebuffers(1, &renderID);
	}

	void GL4FrameBuffer::bind(){
		glBindFramebuffer(GL_FRAMEBUFFER, renderID);
	}

	//TODO: add an isBound function to the bindable class

	void GL4FrameBuffer::attachTexture(Texture& texture, AttachmentType attachmentType){
		glBindFramebuffer(GL_FRAMEBUFFER, renderID);
		
		const unsigned int textureRenderID = static_cast<GL4Texture&>(texture).getRenderID();
		int glAttachType = -1;
		switch (attachmentType){
			case AttachmentType::Colour:
				glAttachType = GL_COLOR_ATTACHMENT0;
				break;

			case AttachmentType::Depth:
				glAttachType = GL_DEPTH_ATTACHMENT;
				break;

			case AttachmentType::Stencil:
				glAttachType = GL_STENCIL_ATTACHMENT;
				break;

			case AttachmentType::Depth_Stencil:
				glAttachType = GL_DEPTH_STENCIL_ATTACHMENT;
				break;
		
			default:
				CLV_ASSERT(false, "{0}: Unhandled attachment type", __func__);
				break;
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, glAttachType, GL_TEXTURE_2D, textureRenderID, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool GL4FrameBuffer::isComplete() const{
		glBindFramebuffer(GL_FRAMEBUFFER, renderID);
		const bool result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return result;
	}
}