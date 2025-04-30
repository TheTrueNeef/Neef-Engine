#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <vector>
#include <string>

class Scene {
private:
    std::vector<GameObject*> gameObjects; // List of game objects in the scene
    std::string sceneName; // Name of the scene, used for JSON file creation

public:
    // Constructor with scene name
    Scene(const std::string& name);
    ~Scene();

    GameObject* selected = nullptr;

    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* gameObject);
    void ClearScene();

    GameObject* GetGameObjectByIndex(size_t index);          // Get GameObject by index
    GameObject* GetGameObjectByName(const std::string& name); // Get GameObject by name
    GameObject* RaycastSelect(Camera3D camera, PhysicsManager& physManager);
    void Update();
    void Draw();

    // Save the scene's current state to a JSON file
    void SaveToJSON() const;
};

#endif // SCENE_H
