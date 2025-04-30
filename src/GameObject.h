#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"
#include <string>
#include "json.hpp"
#include <btBulletDynamicsCommon.h>
#include "PhysicsManager.h"

using json = nlohmann::json;

enum class ColliderType {
    Box,
    Sphere,
    Capsule,
    Cylinder,
    Cone,
    Plane,
    None
};

class GameObject {
private:
    Vector3 position;
    Vector3 rotation;
    float scale;
    Model model;
    Texture texture;
    Color color = WHITE;
    void SaveToJson();

public:
    // Physics-related properties
    struct PhysicsComponent {
        float mass{1.0f};
        bool affectedByGravity{false};
        bool canCollide{false};
        Vector3 originalPosition; // Backup for reset
        btRigidBody* rigidBody{nullptr}; // Bullet RigidBody
    } physics;

    ColliderType colliderType = ColliderType::Box;

    json jsonData;
    std::string jsonFilename;
    bool isSelected{false};
    int CUBE_ID{0}, MODEL_ID{1};

    GameObject(int modelID, const std::string& modelPath, const std::string& texturePath, const std::string& jsonFilename);
    ~GameObject();

    // Setters
    void SetPosition(Vector3 pos);
    void SetRotation(Vector3 rot);
    void SetScale(float s);
    void SetColor(Color c);
    void SetColliderType(ColliderType type) { colliderType = type; }

    // Getters
    Vector3 GetPosition() const;
    Vector3 GetRotation() const;
    float GetScale() const;
    ColliderType GetColliderType() const { return colliderType; }

    // Physics setup
    void SetupPhysics(btDiscreteDynamicsWorld* world);
    void RemovePhysics(btDiscreteDynamicsWorld* world);
    void ResetPosition();
    void UpdatePhysics(btDiscreteDynamicsWorld* world);
    
    void DrawColliderDebug();
    void Update();
    void Draw();
    void clear();
};

#endif // GAMEOBJECT_H
