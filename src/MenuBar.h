#ifndef MENUBAR_H
#define MENUBAR_H

#include "C:/msys64/ucrt64/include/raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>
#include "mouse_movement.h"
#include "rlImGui.h"
#include "imgui.h"
#include "imgui_impl_raylib.h"
#include "gameobject.h"
#include "Scene.h"
#include "json.hpp"
using json = nlohmann::json; // Alias the namespace for easier usage

class MenuBar {
public:
    void ShowMenuBar(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot);
};

#endif // MENUBAR_H
