#pragma once

#include "Clove/ECS/System.hpp"

#include "Clove/ECS/3D/Components/TransformComponent.hpp"
#include "Clove/ECS/3D/Components/LightComponent.hpp"

namespace clv::ecs::d3{
	class LightSystem : public System<TransformComponent, LightComponent>{
		//FUNCTIONS
	public:
		LightSystem();
		LightSystem(const System& other) = delete;
		LightSystem(LightSystem&& other) noexcept;
		LightSystem& operator=(const LightSystem& other) = delete;
		LightSystem& operator=(LightSystem&& other) noexcept;
		virtual ~LightSystem();

		virtual void update(utl::DeltaTime deltaTime) override;
	};
}