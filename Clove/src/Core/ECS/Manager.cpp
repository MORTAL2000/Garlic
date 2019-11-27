#include "Manager.hpp"

#include "Core/ECS/Entity.hpp"
#include "Core/ECS/2D/Systems/RenderSystem.hpp"
#include "Core/ECS/2D/Systems/PhysicsSystem.hpp"
#include "Core/ECS/3D/Systems/RenderSystem.hpp"
#include "Core/ECS/3D/Systems/PhysicsSystem.hpp"
#include "Core/ECS/Audio/Systems/AudioSystem.hpp"

namespace clv::ecs{
	EntityID Manager::nextID = 1;

	Manager::Manager(){
		//Order is somewhat important
		systems.reserve(5);
		systems.push_back(std::make_unique<_3D::PhysicsSystem>());
		systems.push_back(std::make_unique<_3D::RenderSystem>());

		systems.push_back(std::make_unique<_2D::PhysicsSystem>());
		systems.push_back(std::make_unique<_2D::RenderSystem>());

		systems.push_back(std::make_unique<aud::AudioSystem>());

		std::for_each(systems.begin(), systems.end(), [this](const std::unique_ptr<System>& system){
			system->manager = this;
		});

		componentManager.componentAddedDelegate.bind(&Manager::onComponentAdded, this);
		componentManager.componentRemovedDelegate.bind(&Manager::onComponentRemoved, this);
	}

	Manager::~Manager() = default;

	void Manager::update(utl::DeltaTime deltaTime){
		std::for_each(systems.begin(), systems.end(), [](const std::unique_ptr<System>& system){
			system->preUpdate();
		});

		std::for_each(systems.begin(), systems.end(), [deltaTime](const std::unique_ptr<System>& system){
			system->update(deltaTime);
		});

		std::for_each(systems.begin(), systems.end(), [](const std::unique_ptr<System>& system){
			system->postUpdate();
		});
	}

	Entity Manager::createEntity(){
		return { nextID++, this };
	}

	Entity Manager::getEntity(EntityID ID){
		if(ID == INVALID_ENTITY_ID){
			return {};
		} else{
			return { ID, this };
		}
	}

	void Manager::destroyEntity(EntityID ID){
		if(ID == INVALID_ENTITY_ID){
			return;
		}
		componentManager.onEntityDestroyed(ID);
	}

	void Manager::onComponentAdded(ComponentInterface* component){
		std::for_each(systems.begin(), systems.end(), [component](const std::unique_ptr<System>& system){
			system->onComponentCreated(component);
		});
	}

	void Manager::onComponentRemoved(ComponentInterface* component){
		std::for_each(systems.begin(), systems.end(), [component](const std::unique_ptr<System>& system){
			system->onComponentDestroyed(component);
		});
	}
}