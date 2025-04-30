#include "Scene.h"
#include <algorithm>
#include <fstream> // For file operations
#include <iostream> // For error reporting
#include <string>
#include "json.hpp"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

using json = nlohmann::json; // Alias the namespace for easier usage

// Constructor
Scene::Scene(const std::string& name) : sceneName(name) {
    // Create the initial JSON data
    json sceneData;
    sceneData["sceneName"] = sceneName;
    sceneData["gameObjects"] = json::array(); // Start with an empty array

    // File name for the JSON file
    std::string fileName = sceneName + ".json";

    // Write the JSON data to the file
    try {
        std::ofstream file(fileName);
        if (file.is_open()) {
            file << sceneData.dump(4); // Pretty print with 4 spaces
            file.close();
        } else {
            std::cerr << "Error: Could not open file " << fileName << " for writing." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error writing JSON file: " << e.what() << std::endl;
    }
}

// Destructor
Scene::~Scene() {
    ClearScene();
}

// Add a GameObject to the scene
void Scene::AddGameObject(GameObject* gameObject) {
    if(selected != nullptr)
    {
        selected->isSelected = false;
    }
    gameObject->isSelected = true;
    selected = gameObject;
    gameObjects.push_back(gameObject);
}

// Remove a GameObject from the scene
void Scene::RemoveGameObject(GameObject* gameObject) {
    gameObjects.erase(
        std::remove(gameObjects.begin(), gameObjects.end(), gameObject),
        gameObjects.end()
    );
    delete gameObject;
}

// Clear all GameObjects from the scene
void Scene::ClearScene() {
    for (auto* gameObject : gameObjects) {
        delete gameObject;
    }
    gameObjects.clear();
}

// Update all GameObjects
void Scene::Update() {
    for (auto* gameObject : gameObjects) {
        gameObject->Update();
    }
}


GameObject* Scene::RaycastSelect(Camera3D camera, PhysicsManager& physManager) {
    Vector2 mousePos = GetMousePosition();

    Ray ray = GetMouseRay(mousePos, camera);
    btVector3 rayFrom(ray.position.x, ray.position.y, ray.position.z);
    btVector3 rayTo(ray.position.x + ray.direction.x * 1000,
                    ray.position.y + ray.direction.y * 1000,
                    ray.position.z + ray.direction.z * 1000);

    btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);
    physManager.GetWorld()->rayTest(rayFrom, rayTo, rayCallback);

    if (rayCallback.hasHit()) {
        btRigidBody* hitBody = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
        for (GameObject* obj : gameObjects) {
            if (obj->physics.rigidBody == hitBody) {
                return obj;
            }
        }
    }
    return nullptr;
}

// Draw all GameObjects
void Scene::Draw() 
{
    DrawGrid(1000,1.0f);
    for (auto* gameObject : gameObjects) {
        gameObject->Draw();
    }
}
