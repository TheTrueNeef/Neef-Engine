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
    // Load model and texture
    //model = LoadModel("../resources/Rv.obj");
    texture = LoadTexture(texturePath.c_str());
    // 0 Cube, 1 Sphere, 2 Model
    switch (modelID)
    {
    case 0:
        model = LoadModelFromMesh(GenMeshCube(1.0f,1.0f,1.0f));
        break;
    case 1:
        try
        {
            Mesh sphere = GenMeshSphere(1.0f,50,50);
            model = LoadModelFromMesh(sphere);
        }        
        catch(_exception e)
        {
            model = LoadModelFromMesh(GenMeshCube(1.0f,1.0f,1.0f));
        }
        break;
    case 2:
        model = LoadModel(modelPath.c_str());
        texture = LoadTexture(texturePath.c_str());

        // Associate texture with model
        std::cout << "Model Material Count: " << model.materialCount << std::endl;
        for (int i = 0; i < model.materialCount; i++) 
        {
            model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
        }
        if (texture.id == 0) 
        {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
        break;
    default:
        break;
    }

    // Load JSON data
    // std::ifstream file(jsonPath);
    // if (file.is_open()) {
    //     try {
    //         file >> jsonData;
    //     } catch (const std::exception& e) {
    //         std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
    //         jsonData = {}; // Default empty JSON
    //     }
    //     file.close();
    // } else {
    //     std::cerr << "JSON file not found: " << jsonPath << ". Using default values.\n";
    //     jsonData = {
    //         {"position", {{"x", 0.0f}, {"y", 0.0f}, {"z", 0.0f}}},
    //         {"rotation", {{"x", 0.0f}, {"y", 0.0f}, {"z", 0.0f}}},
    //         {"scale", 1.0f}
    //     };
    // }
}

// Destructor
GameObject::~GameObject() {
    UnloadModel(model);
    UnloadTexture(texture);
}

// Setters
void GameObject::SetPosition(Vector3 pos) {
    position = {pos.x, pos.y, pos.z};
    jsonData["position"] = {{"x", pos.x}, {"y", pos.y}, {"z", pos.z}};
}

void GameObject::SetRotation(Vector3 rot) {
    rotation = rot; // Update internal rotation
    model.transform = MatrixRotateXYZ((Vector3){DEG2RAD * rot.x, DEG2RAD * rot.y, DEG2RAD * rot.z});
    jsonData["rotation"] = {{"x", rot.x}, {"y", rot.y}, {"z", rot.z}};
}

void GameObject::SetScale(float s) {
    scale = s;
    jsonData["scale"] = s;
}

void GameObject::SetColor(Color c)
{
    color = c;
}

// Getters
Vector3 GameObject::GetPosition() const {
    return position;
}

Vector3 GameObject::GetRotation() const {
    return rotation;
}

float GameObject::GetScale() const {
    return scale;
}

// Update method
void GameObject::Update() {
    // Apply physics and user input here if needed
}

// Draw method
void GameObject::Draw() {
    // Scale bounding box based on the object's scale
    //Draw Model
    if(isSelected)
    {
        DrawCubeWires(position, scale + 0.1f, scale + 0.1f, scale + 0.1f, RED);
    }
    DrawModel(model, position, scale, color);
}

void GameObject::clear()
{
    GameObject::~GameObject();
}