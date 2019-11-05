#include "RigidBodyComponent.hpp"

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>

namespace clv::ecs::_2D{
	RigidBodyComponent::RigidBodyComponent(){
		initialise({ 1.0f, 1.0f });
	}

	RigidBodyComponent::RigidBodyComponent(RigidBodyComponent&& other) noexcept{
		onBodyCollision = std::move(other.onBodyCollision);

		collisionShape = std::move(other.collisionShape);
		body = std::move(other.body);

		mass = std::move(other.mass);
		isKinematic = std::move(other.isKinematic);
	}

	RigidBodyComponent& RigidBodyComponent::operator=(RigidBodyComponent&& other) noexcept{
		onBodyCollision = std::move(other.onBodyCollision);

		collisionShape = std::move(other.collisionShape);
		body = std::move(other.body);

		mass = std::move(other.mass);
		isKinematic = std::move(other.isKinematic);

		return *this;
	}

	RigidBodyComponent::~RigidBodyComponent() = default;

	RigidBodyComponent::RigidBodyComponent(float mass, bool isKinematic, const math::Vector2f& cubeSize)
		: mass(mass)
		, isKinematic(isKinematic){
		initialise(cubeSize);
	}

	void RigidBodyComponent::initialise(const math::Vector2f& squareSize){
		collisionShape = std::make_unique<btBox2dShape>(btVector3{ squareSize.x, squareSize.y, 0.0f });

		btVector3 localInertia(0, 0, 0);
		btTransform startTransform;
		startTransform.setIdentity();

		if(isKinematic){
			CLV_LOG_WARN("Kinematic body has non 0 mass. Setting to 0");
			mass = 0.0f;
		} else{
			collisionShape->calculateLocalInertia(mass, localInertia);
		}

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collisionShape.get(), localInertia);

		body = std::make_unique<btRigidBody>(rbInfo);
		body->setUserPointer(this);
		if(isKinematic){
			body->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT); //Kinematic objects can't move but static can - seems to be the opposite of what I read
		}
	}
}