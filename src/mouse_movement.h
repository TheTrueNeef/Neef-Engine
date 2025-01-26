#ifndef MOUSE_MOVEMENT_H
#define MOUSE_MOVEMENT_H

#include "raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>

// Function declaration for updating camera based on mouse movement
Vector3 GetCameraForward(Camera camera); 

Vector3 GetCameraRight(Camera camera); 

Vector3 GetCameraUp(Camera camera);

void UpdateMouseMovement(Camera3D* camera);

#endif
