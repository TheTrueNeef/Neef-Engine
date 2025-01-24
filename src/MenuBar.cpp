#include "MenuBar.h"
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
#include <cstdio>
using json = nlohmann::json; // Alias the namespace for easier usage

void MenuBar::ShowMenuBar(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot) {
    // Use the custom font if it's available
    if (customFont) {
        ImGui::PushFont(customFont);
    }
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg].w = 1.0f; // Set the background alpha to 1.0 (fully opaque)

    // Adjust style for the menu bar
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 15)); // Larger frame padding
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(30, 5));  // Space out items
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    // Begin the main menu bar
    if (ImGui::BeginMainMenuBar()) {
        // File menu
        if (ImGui::BeginMenu("\uf07c File")) {
            if (ImGui::MenuItem("\uf15b New Project", "Ctrl+N")) {
                // Action for creating a new project
            }
            if (ImGui::MenuItem("\uf07c Open Project", "Ctrl+O")) {
                // Action for opening a project
            }
            if (ImGui::MenuItem("\uf0c7 Save Project", "Ctrl+S")) {
                // Action for saving a project
            }
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                // Action for exiting the application
            }
            ImGui::EndMenu();
        }

        // Edit menu
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
                // Action for undo
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
                // Action for redo
            }
            if (ImGui::MenuItem("Preferences")) {
                // Action for opening preferences
            }
            ImGui::EndMenu();
        }

        // Help menu
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("\uf059 Documentation", "F1")) 
            {
                system("start https://neefengine.com/docs");
            }
            if (ImGui::MenuItem("\uf05a About")) 
            {
                // Action to show about dialog
            }
            ImGui::EndMenu();
        }

        // Start menu
        if (ImGui::BeginMenu("Start")) 
        {
            if (ImGui::MenuItem("Run Game Windowed", "F1")) {
                // Action to open documentation
            }
            if (ImGui::MenuItem("Run Fullscreen")) {
                // Action to show about dialog
            }
            ImGui::EndMenu();
        }

        // Stop menu
        if (ImGui::BeginMenu("Stop")) 
        {
            if (ImGui::MenuItem("\uf059 Stop", "F1")) 
            {
                // Action to stop code
            }
            ImGui::EndMenu();
        }

        // Windows menu
        if (ImGui::BeginMenu("Windows")) 
        {
            if (ImGui::MenuItem("\uf059 None", "F1")) 
            {
                // Action to stop code
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Revert style changes
    ImGui::PopStyleVar(2);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.2f, 0.6f, 0.8f));      // Button color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.3f, 0.7f, 0.9f)); // Hovered color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.1f, 0.5f, 1.0f));  // Active color

    const float menuWidth = 400.0f;
    const float menuHeight = GetScreenHeight() -50.0f;
    const float menuPos = 42.0f;
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    // Left Menu
    ImGui::SetNextWindowPos(ImVec2(0, menuPos)); // Position: Top-left corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight)); // Size: 400px wide, screen height - 50px
    //ImGui::SetWindowFontScale(10.0f); // Scale text in the current window
    ImGui::Begin("Objects In Scene", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Objects In Scene");
    ImGui::Separator();
    // Add content for the left menu here
    if(ImGui::BeginTabBar("Objects"))
    {
        if(ImGui::TabItemButton("Add"))
        {
            
        }
        if(ImGui::TabItemButton("Remove"))
        {

        }
        if(ImGui::TabItemButton("New Scene"))
        {

        }
    }
    ImGui::Text("Option 1");
    ImGui::Text("Option 2");
    ImGui::Text("Option 3");
    
    ImGui::EndTabBar();
    ImGui::End();
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    // Right Menu
    ImGui::SetNextWindowPos(ImVec2(GetScreenWidth() - menuWidth, menuPos)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight)); // Size: 400px wide, screen height - 50px
    ImGui::Begin("Right Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Right Side Menu");
    ImGui::Separator();
    //Cordinates
    if(ImGui::BeginTabBar("Object Inspector"))
    {
        if(ImGui::TabItemButton("Properties"))
        {

        }
        if(ImGui::TabItemButton("Shaders and Materials"))
        {

        }
        if(ImGui::TabItemButton("Animations"))
        {

        }
    }
    ImGui::EndTabBar();
    ImGui::Text("Vector Space Position and Rotation");
    char coordinates[50];
    sprintf(coordinates, "X: %.2f, Y: %.2f, Z: %.2f", camMain.position.x, camMain.position.y, camMain.position.z);
    char target[50];
    sprintf(target, "X: %.2f, Y: %.2f, Z: %.2f", camMain.target.x, camMain.target.y, camMain.target.z);
    ImGui::Text(coordinates);
    ImGui::Text(target);
    ImGui::Separator();
    ImGui::Text("Object Transform");
    ImGui::Text("Current Value: %.2f", pos.x);
    ImGui::SliderFloat("X:", &pos.x, -100.0f, 100.0f, "Value: %.2f");
    ImGui::Text("Current Value: %.2f", pos.y);
    ImGui::SliderFloat("Y:", &pos.y, -100.0f, 100.0f, "Value: %.2f");
    ImGui::Text("Current Value: %.2f", pos.z);
    ImGui::SliderFloat("Z:", &pos.z, -100.0f, 100.0f, "Value: %.2f");
    ImGui::Separator();
    ImGui::Text("Object Rotation");
    ImGui::Text("Current Value: %.2f", rot.x);
    ImGui::SliderFloat("Pitch:", &rot.x, -360.0f, 360.0f, "Value: %.2f");
    ImGui::Text("Current Value: %.2f", rot.y);
    ImGui::SliderFloat("Yaw:", &rot.y, -360.0f, 360.0f, "Value: %.2f");
    ImGui::Text("Current Value: %.2f", rot.z);
    ImGui::SliderFloat("Roll:", &rot.z, -360.0f, 360.0f, "Value: %.2f");
    ImGui::Separator();
    ImGui::End();
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    // Bottom Menu
    ImGui::SetNextWindowPos(ImVec2(menuWidth, 750.0f)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth() - 2.0f*menuWidth, menuPos + 330.0f)); // Size: 400px wide, screen height - 50px
    ImGui::Begin("File Manager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("File Manager");
    ImGui::Separator();
    // Add content for the Bottom menu here
    ImGui::Text("Option A");
    ImGui::Text("Option B");
    ImGui::Text("Option C");
    
    ImGui::End();

    // Revert to default font if custom font was used
    if (customFont) {
        ImGui::PopFont();
    }
    ImGui::PopStyleColor(3);
}
