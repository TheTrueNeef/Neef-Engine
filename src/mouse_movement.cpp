#include "raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>

//g++ main.cpp mouse_movement.cpp -o main -L"C:/msys64/ucrt64/lib" -I"C:/msys64/ucrt64/include" -lraylib -lopengl32 -lgdi32 -lwinmm

Vector3 GetCameraForward(Camera camera) {
    Vector3 forward = Vector3Subtract(camera.target, camera.position);
    return Vector3Normalize(forward);  // Normalize to ensure consistent movement speed
}

// Function to get the normalized right direction of the camera
Vector3 GetCameraRight(Camera camera) {
    Vector3 forward = GetCameraForward(camera);  // Get the forward direction
    Vector3 right = Vector3CrossProduct(camera.up, forward);  // Perpendicular vector
    return Vector3Normalize(right);  // Normalize to ensure consistent movement speed
}

// Function to get the normalized up direction of the camera
Vector3 GetCameraUp(Camera camera) {
    Vector3 forward = GetCameraForward(camera);  // Get the forward direction
    Vector3 up = Vector3CrossProduct(forward, GetCameraRight(camera));  // Perpendicular vector
    return Vector3Normalize(up);  // Normalize to ensure consistent movement speed
}

void UpdateMouseMovement(Camera3D* camera) {

    Vector2 mousePosition = GetMousePosition();
    Vector2 windowPosition = GetWindowPosition();
    
    // Adjust mouse position to loop within the window
    if (mousePosition.x < 0) {
        SetMousePosition(GetScreenWidth() - 1 + windowPosition.x, mousePosition.y + windowPosition.y);
    } else if (mousePosition.x > GetScreenWidth()) {
        SetMousePosition(1 + windowPosition.x, mousePosition.y + windowPosition.y);
    }

    if (mousePosition.y < 0) {
        SetMousePosition(mousePosition.x + windowPosition.x, GetScreenHeight() - 1 + windowPosition.y);
    } else if (mousePosition.y > GetScreenHeight()) {
        SetMousePosition(mousePosition.x + windowPosition.x, 1 + windowPosition.y);
    }

    // Window dimensions
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();

    UpdateCamera(camera, CAMERA_FIRST_PERSON);

    if (mousePosition.x < 1) {
        SetMousePosition(windowWidth - 1, mousePosition.y);  // Wrap to the right edge
    } else if (mousePosition.x >= windowWidth) {
        SetMousePosition(0, mousePosition.y);  // Wrap to the left edge
    }

    if (mousePosition.y < 1) {
        SetMousePosition(mousePosition.x, windowHeight - 1);  // Wrap to the bottom edge
    } else if (mousePosition.y >= windowHeight) {
        SetMousePosition(mousePosition.x, 0);  // Wrap to the top edge
    }

    Vector3 moveDirection = {0.0f, 0.0f, 0.0f};

    Vector3 forward = GetCameraForward(*camera);
    Vector3 right = GetCameraRight(*camera);
    Vector3 up = GetCameraUp(*camera);

    if (IsKeyDown(KEY_W)) moveDirection = Vector3Add(moveDirection, forward);   // Move forward
    if (IsKeyDown(KEY_S)) moveDirection = Vector3Subtract(moveDirection, forward); // Move backward
    if (IsKeyDown(KEY_A)) moveDirection = Vector3Add(moveDirection, right); // Move left
    if (IsKeyDown(KEY_D)) moveDirection = Vector3Subtract(moveDirection, right);   // Move right
    if (IsKeyDown(KEY_SPACE)) moveDirection = Vector3Add(moveDirection, up);   // Move up
    if (IsKeyDown(KEY_LEFT_SHIFT)) moveDirection = Vector3Subtract(moveDirection, up); // Move down

    camera->position = Vector3Add(camera->position, moveDirection);
    camera->target = Vector3Add(camera->target, moveDirection);
}

