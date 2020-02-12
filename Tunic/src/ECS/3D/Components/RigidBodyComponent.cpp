#include "Tunic/ECS/3D/Components/RigidBodyComponent.hpp"

#include <btBulletDynamicsCommon.h>

using namespace clv;

namespace tnc::ecs::_3D{
	RigidBodyComponent::RigidBodyComponent(){
		initialise({ 1.0f, 1.0f, 1.0f });
	}

	RigidBodyComponent::RigidBodyComponent(float mass, bool isKinematic, const mth::vec3f& cubeSize)
		: mass(mass)
		, isKinematic(isKinematic){
		initialise(cubeSize);
	}

	RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other){
		mass = other.mass;
		isKinematic = other.isKinematic;

		initialise(other.cubeSize);
	}

	RigidBodyComponent::RigidBodyComponent(RigidBodyComponent&& other) noexcept{
		onBodyCollision = std::move(other.onBodyCollision);
		
		collisionShape = std::move(other.collisionShape);
		body = std::move(other.body);

		mass = other.mass;
		isKinematic = other.isKinematic;
	}

	RigidBodyComponent& RigidBodyComponent::operator=(const RigidBodyComponent& other){
		mass = other.mass;
		isKinematic = other.isKinematic;

		initialise(other.cubeSize);

		return *this;
	}

	RigidBodyComponent& RigidBodyComponent::operator=(RigidBodyComponent&& other) noexcept{
		onBodyCollision = std::move(other.onBodyCollision);

		collisionShape = std::move(other.collisionShape);
		body = std::move(other.body);

		mass = other.mass;
		isKinematic = other.isKinematic;

		return *this;
	}

	RigidBodyComponent::~RigidBodyComponent() = default;

	void RigidBodyComponent::initialise(const mth::vec3f& cubeSize){
		this->cubeSize = cubeSize;

		collisionShape = std::make_unique<btBoxShape>(btVector3{ cubeSize.x, cubeSize.y, cubeSize.z });

		btVector3 localInertia(0, 0, 0);
		btTransform startTransform;
		startTransform.setIdentity();

		if(isKinematic){
			CLV_LOG_WARN("Kinematic body has non 0 mass. Setting to 0");
			mass = 0.0f;
		} else{
			collisionShape->calculateLocalInertia(mass, localInertia);
		}

		auto* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collisionShape.get(), localInertia);

		body = std::make_unique<btRigidBody>(rbInfo);
		body->setUserPointer(this);
		if(isKinematic){
			body->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT); //Kinematic objects can't move but static can - seems to be the opposite of what I read
		}
	}
}