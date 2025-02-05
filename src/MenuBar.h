#ifndef MENUBAR_H
#define MENUBAR_H

#include "raylib.h"
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
#include "ToggleState.h"

using json = nlohmann::json; // Alias the namespace for easier usage

class MenuBar {
public:
    void ShowMenuBar(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot,Scene* sc, float& scale, ToggleState& state, Vector3& color);
    void ProjSelect(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot,Scene* sc, float& scale);

};

#endif // MENUBAR_H