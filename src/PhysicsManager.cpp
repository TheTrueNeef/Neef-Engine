#include "PhysicsManager.h"
#include "GameObject.h" // Now safe since PhysicsManager.h only forward-declares it

PhysicsManager::PhysicsManager() {
    broadphase = new btDbvtBroadphase();
    collisionConfig = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfig);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
    world->setGravity(btVector3(0, -9.81f, 0));
}

PhysicsManager::~PhysicsManager() {
    delete world;
    delete solver;
    delete dispatcher;
    delete collisionConfig;
    delete broadphase;
}

void PhysicsManager::AddObject(GameObject* obj) {
    physicsObjects.push_back(obj);
}

void PhysicsManager::StartSimulation() {
    if (isSimulating) return;
    isSimulating = true;
    for (auto* obj : physicsObjects) {
        obj->SetupPhysics(world);
    }
}

void PhysicsManager::StopSimulation() {
    if (!isSimulating) return;
    isSimulating = false;
    for (auto* obj : physicsObjects) {
        obj->RemovePhysics(world);
        obj->ResetPosition();
    }
}

void PhysicsManager::Update(float dt) {
    if (!isSimulating) return;

    world->stepSimulation(dt);
    for (auto* obj : physicsObjects) {
        if (obj->physics.rigidBody) {
            btTransform trans;
            obj->physics.rigidBody->getMotionState()->getWorldTransform(trans);
            btVector3 pos = trans.getOrigin();
            obj->SetPosition({pos.getX(), pos.getY(), pos.getZ()});
        }
    }
}
