#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <vector>
#include <btBulletDynamicsCommon.h>

// Forward declare GameObject to avoid circular include
class GameObject;

class PhysicsManager {
public:
    PhysicsManager();
    ~PhysicsManager();

    void AddObject(GameObject* obj);
    void StartSimulation();
    void StopSimulation();
    void Update(float dt);

    bool IsSimulating() const { return isSimulating; }

    btDiscreteDynamicsWorld* GetWorld() const { return world; }
private:
    bool isSimulating = false;
    std::vector<GameObject*> physicsObjects;

    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfig;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
};

#endif
