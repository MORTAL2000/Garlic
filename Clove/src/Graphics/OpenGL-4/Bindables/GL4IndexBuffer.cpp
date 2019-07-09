#include "clvpch.hpp"
#include "GL4IndexBuffer.hpp"

#include "Clove/Graphics/RenderCommand.hpp"

#include <glad/glad.h>

namespace clv::gfx{
	GL4IndexBuffer::GL4IndexBuffer(GL4IndexBuffer&& other) noexcept = default;

	GL4IndexBuffer& GL4IndexBuffer::operator=(GL4IndexBuffer&& other) noexcept = default;

	GL4IndexBuffer::~GL4IndexBuffer(){
		glDeleteBuffers(1, &bufferID);
	}

	GL4IndexBuffer::GL4IndexBuffer(const std::vector<unsigned int>& indices){
		count = static_cast<unsigned int>(indices.size());
		const auto dataSize = count * static_cast<GLsizeiptr>(sizeof(unsigned int));

		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, indices.data(), GL_STATIC_DRAW);
	}

	void GL4IndexBuffer::bind(){
		RenderCommand::setIndexBuffer(*this);
	}

	void GL4IndexBuffer::unbind(){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int GL4IndexBuffer::getIndexCount() const{
		return count;
	}
	
	unsigned int GL4IndexBuffer::getBufferID() const{
		return bufferID;
	}
}