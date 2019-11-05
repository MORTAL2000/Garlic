#pragma once

#include "Core/Graphics/Material.hpp"
#include "Core/Graphics/Bindables/ShaderBufferObject.hpp"
#include "Core/Graphics/Bindables/Shader.hpp" //TODO: Remove? needed for the shader reflection data

//TODO: Move this into the material file???
namespace clv::gfx{
	class Material;
	class Texture;

	class MaterialInstance{
		//VARIABLES
	private:
		std::shared_ptr<Material> material;
		std::shared_ptr<Texture> albedoTexture;
		std::shared_ptr<Texture> specTexture;
		std::unordered_map<BufferBindingPoint, std::shared_ptr<Bindable>> shaderData;

		//FUNCTIONS
	public:
		MaterialInstance() = delete;
		MaterialInstance(const MaterialInstance& other);
		MaterialInstance& operator=(const MaterialInstance& other);
		MaterialInstance(MaterialInstance&& other) noexcept;
		MaterialInstance& operator=(MaterialInstance&& other) noexcept;

		MaterialInstance(std::shared_ptr<Material> material);

		void bind();

		const ShaderReflectionData& getReflectionData() const;
		const std::shared_ptr<Shader>& getShader() const;

		template<typename DataType>
		void setData(BufferBindingPoint bindingPoint, DataType&& data, gfx::ShaderType shaderType);

		void setAlbedoTexture(const std::string& path);
		void setAlbedoTexture(const std::shared_ptr<Texture>& texture);

		void setSpecularTexture(const std::string& path);
		void setSpecularTexture(const std::shared_ptr<Texture>& texture);
	};
}

#include "MaterialInstance.inl"