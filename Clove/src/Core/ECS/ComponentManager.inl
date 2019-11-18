namespace clv::ecs{
	template<typename ComponentType>
	ComponentManager::ComponentContainer<ComponentType>::ComponentContainer() = default;

	template<typename ComponentType>
	ComponentManager::ComponentContainer<ComponentType>::ComponentContainer(const ComponentContainer& other) = default;

	template<typename ComponentType>
	ComponentManager::ComponentContainer<ComponentType>::ComponentContainer(ComponentContainer&& other) noexcept = default;

	template<typename ComponentType>
	ComponentManager::ComponentContainer<ComponentType>& ComponentManager::ComponentContainer<ComponentType>::operator=(const ComponentContainer& other) = default;

	template<typename ComponentType>
	ComponentManager::ComponentContainer<ComponentType>& ComponentManager::ComponentContainer<ComponentType>::operator=(ComponentContainer&& other) noexcept = default;

	template<typename ComponentType>
	ComponentManager::ComponentContainer<ComponentType>::~ComponentContainer() = default;

	template<typename ComponentType>
	template<typename ...ConstructArgs>
	ComponentType* ComponentManager::ComponentContainer<ComponentType>::addComponent(EntityID entityID, ConstructArgs&& ...args){
		auto comp = std::make_unique<ComponentType>(std::forward<ConstructArgs>(args)...);
		comp->entityID = entityID; //TODO: make this container a friend of the component now it's typed
		
		componentAddedDelegate.broadcast(comp.get());
		
		components[entityID] = std::move(comp);
		return components[entityID].get();
	}

	template<typename ComponentType>
	ComponentType* ComponentManager::ComponentContainer<ComponentType>::getComponent(EntityID entityID){
		if(auto iter = components.find(entityID); iter != components.end()){
			return iter->second.get();
		} else{
			return nullptr;
		}
	}

	template<typename ComponentType>
	void ComponentManager::ComponentContainer<ComponentType>::removeComponent(EntityID entityID){
		if(auto iter = components.find(entityID); iter != components.end()){
			componentRemovedDelegate.broadcast(iter->second.get());
			components.erase(entityID);
		}
	}

	template<typename ComponentType>
	ComponentManager::ComponentContainer<ComponentType>* ComponentManager::getComponentContainer(){
		const ComponentID componentID = ComponentType::id();
		if(auto iter = containers.find(componentID); iter != containers.end()){
			return static_cast<ComponentContainer<ComponentType>*>(iter->second.get());
		} else{
			auto container = std::make_unique<ComponentContainer<ComponentType>>();
			container->componentAddedDelegate.bind(&ComponentManager::onContainerAddedComponent, this);
			container->componentRemovedDelegate.bind(&ComponentManager::onContainerRemovedComponent, this);

			containers[componentID] = std::move(container);
			return static_cast<ComponentContainer<ComponentType>*>(containers[componentID].get());
		}
	}
}