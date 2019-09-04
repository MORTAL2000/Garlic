#include "clvpch.hpp"
#include "GL4Shader.hpp"

#include "Clove/Application.hpp"

#include <fstream>
#include <sstream>

namespace clv::gfx{
	GL4Shader::GL4Shader(GL4Shader&& other) noexcept = default;

	GL4Shader& GL4Shader::operator=(GL4Shader&& other) noexcept = default;

	GL4Shader::~GL4Shader(){
		glDeleteProgram(programID);
	}

	GL4Shader::GL4Shader(ShaderStyle style)
		: programID(glCreateProgram()){
		initialise(style);
	}

	void GL4Shader::bind(){
		glUseProgram(programID);
	}

	ShaderReflectionData GL4Shader::getReflectionData(){
		ShaderReflectionData outData;

		GLint attribCount = 0;
		glGetProgramiv(programID, GL_ACTIVE_ATTRIBUTES, &attribCount);
		for(int32 i = 0; i < attribCount; ++i){
			GLchar name[255];
			GLsizei length = 0;
			GLint size = 0;
			GLenum type = 0;

			glGetActiveAttrib(programID, static_cast<GLuint>(i), sizeof(name), &length, &size, &type, name);

			outData.vertexBufferLayout.add(VertexElement::getTypeFromSemantic(name));
		}

		GLint uboCount = 0;
		glGetProgramiv(programID, GL_ACTIVE_UNIFORM_BLOCKS, &uboCount);
		outData.bufferDescriptions.reserve(uboCount);
		for(int32 i = 0; i < uboCount; ++i){
			ShaderBufferDescription bufferDescription;

			GLchar uboName[255];
			GLsizei uboNameLength = 0;
			glGetActiveUniformBlockName(programID, i, sizeof(uboName), &uboNameLength, uboName);
			
			bufferDescription.name = uboName;

			GLint uboBindingPoint = 0;
			glGetActiveUniformBlockiv(programID, i, GL_UNIFORM_BLOCK_BINDING, &uboBindingPoint);

			bufferDescription.bindingPoint = static_cast<uint32>(uboBindingPoint);

			GLint uboSize = 0;
			glGetActiveUniformBlockiv(programID, i, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);

			bufferDescription.totalSize = static_cast<size_t>(uboSize);

			GLint uboUniformCount = 0;
			glGetActiveUniformBlockiv(programID, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uboUniformCount);
			
			bufferDescription.variables.reserve(static_cast<size_t>(uboUniformCount));
			
			GLint uboUniformIndices[100] = { 0 };
			glGetActiveUniformBlockiv(programID, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, uboUniformIndices);

			//TODO: We'll probably need to author a way to detect arrays (if opengl doesn't have anything to help with that)

			for(int32 j = 0; j < uboUniformCount; ++j){
				GLchar name[255];
				GLsizei length;
				GLint size;
				GLenum type;

				glGetActiveUniform(programID, uboUniformIndices[j], sizeof(name), &length, &size, &type, name);

				bufferDescription.variables.push_back({ name, getVariableType(type), static_cast<size_t>(size) });
			}

			outData.bufferDescriptions.push_back(bufferDescription);
		}

		return outData;
	}

	uint32 GL4Shader::getProgramID() const{
		return programID;
	}

	void GL4Shader::initialise(ShaderStyle style){
		uint32 vertexID = 0;
		uint32 pixelID = 0;
		
		switch(style){
			case ShaderStyle::Lit:
				{
					std::string vertexSource = parseShader("Lit-vs.glsl");
					vertexID = compileShader(GL_VERTEX_SHADER, vertexSource);

					std::string pixelSource = parseShader("Lit-ps.glsl");
					pixelID = compileShader(GL_FRAGMENT_SHADER, pixelSource);
				}
				break;
			case ShaderStyle::Unlit:
				{
					std::string vertexSource = parseShader("Unlit-vs.glsl");
					vertexID = compileShader(GL_VERTEX_SHADER, vertexSource);

					std::string pixelSource = parseShader("Unlit-ps.glsl");
					pixelID = compileShader(GL_FRAGMENT_SHADER, pixelSource);
				}
				break;

			case ShaderStyle::_2D:
				{
					std::string vertexSource = parseShader("2D-vs.glsl");
					vertexID = compileShader(GL_VERTEX_SHADER, vertexSource);

					std::string pixelSource = parseShader("2D-ps.glsl");
					pixelID = compileShader(GL_FRAGMENT_SHADER, pixelSource);
				}
				break;

			case ShaderStyle::RT:
				{
					std::string vertexSource = parseShader("RT-vs.glsl");
					vertexID = compileShader(GL_VERTEX_SHADER, vertexSource);

					std::string pixelSource = parseShader("RT-ps.glsl");
					pixelID = compileShader(GL_FRAGMENT_SHADER, pixelSource);
				}
				break;

			default:
				CLV_ASSERT(false, "Unknown type! {0}", __func__);
				break;
		}

		CLV_ASSERT(vertexID != 0 && pixelID != 0, "Pixel or vertex shader not set!");

		glAttachShader(programID, vertexID);
		glLinkProgram(programID);
		glValidateProgram(programID);
		glDeleteShader(vertexID);

		glAttachShader(programID, pixelID);
		glLinkProgram(programID);
		glValidateProgram(programID);
		glDeleteShader(pixelID);
	}

	std::string GL4Shader::parseShader(const std::string& filepath){
		std::ifstream stream(filepath);

		std::string line;
		std::stringstream ss;
		while(getline(stream, line)){
			ss << line << '\n';
		}

		return ss.str();
	}

	uint32 GL4Shader::compileShader(uint32 type, const std::string& source){
		uint32 id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int32 result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE){
			int32 length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);
			CLV_LOG_ERROR("Failed to compile {0} shader! {1}", type == GL_VERTEX_SHADER ? "vertex" : "fragment", message);
			glDeleteShader(id);
			delete[] message;
		}

		return id;
	}

	BufferVariableType GL4Shader::getVariableType(GLenum glType){
		switch(glType){
			case GL_INT:
				return BufferVariableType::int1;
			case GL_FLOAT:
				return BufferVariableType::float1;
			case GL_FLOAT_VEC2:
				return BufferVariableType::float2;
			case GL_FLOAT_VEC3:
				return BufferVariableType::float3;
			case GL_FLOAT_VEC4:
				return BufferVariableType::float4;
			case GL_FLOAT_MAT4:
				return BufferVariableType::float4_4;

			default:
				CLV_ASSERT(false, "Unhandled GL uniform type {0}", __func__);
				return BufferVariableType::float1;
				break;
		}
	}
}