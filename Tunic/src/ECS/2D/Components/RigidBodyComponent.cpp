#include "Tunic/ECS/2D/Components/RigidBodyComponent.hpp"

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>

using namespace clv;

namespace tnc::ecs::_2D{
	RigidBodyComponent::RigidBodyComponent(){
		initialise({ 1.0f, 1.0f });
	}

	RigidBodyComponent::RigidBodyComponent(float mass, bool isKinematic, bool respondToCollision, const mth::vec2f& cubeSize)
		: mass(mass), isKinematic(isKinematic), respondToCollision(respondToCollision){
		initialise(cubeSize);
	}

	RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other){
		mass = other.mass;
		isKinematic = other.isKinematic;

		initialise(other.squareSize);
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

		initialise(other.squareSize);

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

	void RigidBodyComponent::initialise(const mth::vec2f& squareSize){
		this->squareSize = squareSize;

		collisionShape = std::make_unique<btBox2dShape>(btVector3{ squareSize.x, squareSize.y, 0.0f });

		btVector3 localInertia(0, 0, 0);
		btTransform startTransform;
		startTransform.setIdentity();

		if(isKinematic && mass > 0.0f){
			CLV_LOG_WARN("Kinematic body has non 0 mass. Setting to 0");
			mass = 0.0f;
		} else{
			collisionShape->calculateLocalInertia(mass, localInertia);
		}

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collisionShape.get(), localInertia);

		body = std::make_unique<btRigidBody>(rbInfo);
		body->setUserPointer(this);

		int flags = body->getCollisionFlags();
		if (isKinematic){
			flags |= btCollisionObject::CF_KINEMATIC_OBJECT;
		}
		if (!respondToCollision){
			flags |= btCollisionObject::CF_NO_CONTACT_RESPONSE;
		}
		body->setCollisionFlags(flags);
	}
}