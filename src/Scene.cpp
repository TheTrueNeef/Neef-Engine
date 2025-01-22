#include "Scene.h"
#include <algorithm>
#include <fstream> // For file operations
#include <iostream> // For error reporting
#include <string>
#include "json.hpp"

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

// Draw all GameObjects
void Scene::Draw() {
    for (auto* gameObject : gameObjects) {
        gameObject->Draw();
    }
}
