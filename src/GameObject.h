#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"
#include <string>
#include "json.hpp" // Include the JSON library
using json = nlohmann::json; // Alias the namespace for easier usage

class GameObject {
private:
    Vector3 position;       // Position of the object
    Vector3 rotation;       // Rotation of the object
    float scale;            // Uniform scale factor
    Model model;            // Model of the object
    Texture texture;        // Texture for the model
    Color color = WHITE;
    void SaveToJson();      // Save properties to the JSON file
public:
    json jsonData;          // JSON object to store properties
    std::string jsonFilename; // JSON filename for saving/loading
    bool isSelected{false};
    int CUBE_ID{0}, MODEL_ID{1};
    // Constructor and Destructor
    GameObject(int modelID, const std::string& modelPath, const std::string& texturePath, const std::string& jsonFilename);
    ~GameObject();

    // Setters
    void SetPosition(Vector3 pos);
    void SetRotation(Vector3 rot);
    void SetScale(float s);
    void SetColor(Color c);
    // Getters
    Vector3 GetPosition() const;
    Vector3 GetRotation() const;
    float GetScale() const;

    // Update and Draw
    void Update();
    void Draw();

    void clear();
};

#endif // GAMEOBJECT_H
