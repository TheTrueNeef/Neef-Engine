#include "raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>
#include "mouse_movement.h"
#include "rlImGui.h"
#include "imgui.h"
#include "imgui_impl_raylib.h"
#include <string>
#include <fstream>
#include "GameObject.h"
#include <stdexcept>

// Constructor
GameObject::GameObject(int modelID, const std::string& modelPath, const std::string& texturePath, const std::string& jsonPath) {
    position = {0.0f, 0.0f, 0.0f};
    rotation = {0.0f, 0.0f, 0.0f};
    scale = 1.0f;
    colliderType = ColliderType::Box;

    texture = LoadTexture(texturePath.c_str());
    switch (modelID)
    {
    case 0:
        model = LoadModelFromMesh(GenMeshCube(1.0f,1.0f,1.0f));
        break;
    case 1:
        try {
            Mesh sphere = GenMeshSphere(0.5f,50,50);
            model = LoadModelFromMesh(sphere);
        } catch(_exception e) {
            model = LoadModelFromMesh(GenMeshCube(1.0f,1.0f,1.0f));
        }
        break;
    case 2:
        model = LoadModel(modelPath.c_str());
        texture = LoadTexture(texturePath.c_str());
        std::cout << "Model Material Count: " << model.materialCount << std::endl;
        for (int i = 0; i < model.materialCount; i++) {
            model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
        }
        if (texture.id == 0) {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
        break;
    case 3:
        try {
            Mesh plane = GenMeshPlane(1.0f,1.0f,10,10);
            model = LoadModelFromMesh(plane);
        } catch(_exception e) {
            model = LoadModelFromMesh(GenMeshCube(1.0f,1.0f,1.0f));
        }
        break;
    default:
        break;
    }
}

// Destructor
GameObject::~GameObject() {
    UnloadModel(model);
    UnloadTexture(texture);
}

void GameObject::SetPosition(Vector3 pos) {
    position = {pos.x, pos.y, pos.z};
    jsonData["position"] = { {"x", pos.x}, {"y", pos.y}, {"z", pos.z} };
}

void GameObject::SetRotation(Vector3 rot) {
    rotation = rot;
    model.transform = MatrixRotateXYZ({ DEG2RAD * rot.x, DEG2RAD * rot.y, DEG2RAD * rot.z });
    jsonData["rotation"] = { {"x", rot.x}, {"y", rot.y}, {"z", rot.z} };
}

void GameObject::SetScale(float s) {
    scale = s;
    jsonData["scale"] = s;
}

void GameObject::SetColor(Color c) {
    color = c;
}

Vector3 GameObject::GetPosition() const { return position; }
Vector3 GameObject::GetRotation() const { return rotation; }
float GameObject::GetScale() const { return scale; }

void GameObject::Update() {
    if (physics.rigidBody && physics.rigidBody->getMotionState()) {
        btTransform trans;
        physics.rigidBody->getMotionState()->getWorldTransform(trans);

        // Get position
        btVector3 btPos = trans.getOrigin();
        position = { btPos.getX(), btPos.getY(), btPos.getZ() };

        // Get rotation (as quaternion)
        btQuaternion btRot = trans.getRotation();
        Quaternion q = { btRot.getX(), btRot.getY(), btRot.getZ(), btRot.getW() };

        // Convert quaternion to matrix
        Matrix rotationMatrix = QuaternionToMatrix(q);

        // Apply transform matrix to model
        model.transform = MatrixMultiply(MatrixScale(scale, scale, scale), rotationMatrix);
    }
}

void GameObject::Draw() {
    DrawColliderDebug();
    DrawModel(model, position, scale, color);
}

void GameObject::clear() {
    GameObject::~GameObject();
}

void GameObject::UpdatePhysics(btDiscreteDynamicsWorld* world) {
    RemovePhysics(world);
    SetupPhysics(world);
}

void GameObject::SetupPhysics(btDiscreteDynamicsWorld* world) {
    if (colliderType == ColliderType::None) {
        physics.rigidBody = nullptr;
        return; // Skip physics setup entirely
    }

    physics.originalPosition = position;

    btCollisionShape* shape = nullptr;
    switch (colliderType) {
        case ColliderType::Box:
            shape = new btBoxShape(btVector3(scale / 2, scale / 2, scale / 2));
            break;
        case ColliderType::Sphere:
            shape = new btSphereShape(scale);
            break;
        case ColliderType::Capsule:
            shape = new btCapsuleShape(scale / 2, scale);
            break;
        case ColliderType::Cylinder:
            shape = new btCylinderShape(btVector3(scale / 2, scale / 2, scale / 2));
            break;
        case ColliderType::Cone:
            shape = new btConeShape(scale / 2, scale);
            break;
        case ColliderType::Plane:
            shape = new btBoxShape(btVector3(scale / 2, 0.01f, scale / 2)); // thin in Y axis
            break;
        default:
            shape = new btBoxShape(btVector3(scale / 2, scale / 2, scale / 2));
            break;
    }

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(position.x, position.y, position.z));

    btScalar mass = physics.mass;
    btVector3 inertia(0, 0, 0);
    if (mass > 0.0f)
        shape->calculateLocalInertia(mass, inertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
    physics.rigidBody = new btRigidBody(rbInfo);

    physics.rigidBody->setGravity(physics.affectedByGravity ? btVector3(0, -9.81f, 0) : btVector3(0, 0, 0));
    if (!physics.affectedByGravity) {
        physics.rigidBody->setLinearFactor(btVector3(0, 0, 0));
        physics.rigidBody->setAngularFactor(btVector3(0, 0, 0));
    } else {
        physics.rigidBody->setLinearFactor(btVector3(1, 1, 1));
        physics.rigidBody->setAngularFactor(btVector3(1, 1, 1));
    }

    world->addRigidBody(physics.rigidBody);
}


void GameObject::RemovePhysics(btDiscreteDynamicsWorld* world) {
    if (physics.rigidBody) {
        world->removeRigidBody(physics.rigidBody);
        delete physics.rigidBody->getMotionState();
        delete physics.rigidBody->getCollisionShape();
        delete physics.rigidBody;
        physics.rigidBody = nullptr;
    }
}

void GameObject::ResetPosition() {
    SetPosition(physics.originalPosition);
}

void GameObject::DrawColliderDebug() {
    if (!physics.rigidBody) return;

    Vector3 pos = GetPosition();  // You could also extract it from Bullet if needed
    switch (colliderType) {
        case ColliderType::Box:
            DrawCubeWires(pos, scale, scale, scale, GREEN);
            break;
        case ColliderType::Sphere:
            DrawSphereWires(pos, scale / 2.0f, 12, 12, GREEN);
            break;
        case ColliderType::Capsule:
            // Raylib doesn't have DrawCapsuleWires, approximate with cylinder and spheres
            DrawSphereWires({pos.x, pos.y + scale/2, pos.z}, scale, 12, 12, GREEN);
            DrawCylinderWires(pos, scale / 2.0f, scale / 2.0f, scale, 12, GREEN);
            DrawSphereWires({pos.x, pos.y - scale/2, pos.z}, scale / 2.0f, 12, 12, GREEN);
            break;
        case ColliderType::Cylinder:
            DrawCylinderWires(pos, scale / 2.0f, scale / 2.0f, scale, 12, GREEN);
            break;
        case ColliderType::Cone:
            DrawCylinderWires(pos, 0.0f, scale / 2.0f, scale, 12, GREEN); // narrow tip
            break;
        case ColliderType::Plane:
            DrawCubeWires(pos,scale,0.01f,scale,GREEN);
            break;
        case ColliderType::None:
            break;
    }
}

