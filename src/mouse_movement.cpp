#include "C:/msys64/ucrt64/include/raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>

//g++ main.cpp mouse_movement.cpp -o main -L"C:/msys64/ucrt64/lib" -I"C:/msys64/ucrt64/include" -lraylib -lopengl32 -lgdi32 -lwinmm


void UpdateMouseMovement(Camera3D* camera)
{
        Vector2 mousePosition = GetMousePosition();
        Vector2 windowPosition = GetWindowPosition();

        // Adjust mouse position to loop within the window
        
        if (mousePosition.x < 0) 
        {
            SetMousePosition(GetScreenWidth() - 1 + windowPosition.x, mousePosition.y + windowPosition.y);
        } 
        else if (mousePosition.x > GetScreenWidth()) 
        {
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
        if (mousePosition.x < 1) 
        {
        SetMousePosition(windowWidth - 1, mousePosition.y);  // Wrap to the right edge
        } else if (mousePosition.x >= windowWidth) {
        SetMousePosition(0, mousePosition.y);  // Wrap to the left edge
        }

        if (mousePosition.y < 1) {
        SetMousePosition(mousePosition.x, windowHeight - 1);  // Wrap to the bottom edge
        } else if (mousePosition.y >= windowHeight) {
        SetMousePosition(mousePosition.x, 0);  // Wrap to the top edge
        }
}
