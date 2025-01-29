#include "MenuBar.h"
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
#include <cstdio>
#include "ImGuiFileDialog.h"
using json = nlohmann::json; // Alias the namespace for easier usage

void MenuBar::ShowMenuBar(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot, Scene* sc, float& scale) {
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
            if (ImGui::MenuItem("\uf059 Documentation", "F1")) {
                system("start https://neefengine.com/docs");
            }
            if (ImGui::MenuItem("\uf05a About")) {
                // Action to show about dialog
            }
            ImGui::EndMenu();
        }

        // Start menu
        if (ImGui::BeginMenu("Start")) {
            if (ImGui::MenuItem("Run Game Windowed", "F1")) {
                // Action to open documentation
            }
            if (ImGui::MenuItem("Run Fullscreen")) {
                // Action to show about dialog
            }
            ImGui::EndMenu();
        }

        // Stop menu
        if (ImGui::BeginMenu("Stop")) {
            if (ImGui::MenuItem("\uf059 Stop", "F1")) {
                // Action to stop code
            }
            ImGui::EndMenu();
        }

        // Windows menu
        if (ImGui::BeginMenu("Windows")) {
            if (ImGui::MenuItem("\uf059 None", "F1")) {
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
    const float menuHeight = GetScreenHeight() - 50.0f;
    const float menuPos = 42.0f;
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)

    // Left Menu
    ImGui::SetNextWindowPos(ImVec2(0, menuPos)); // Position: Top-left corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight)); // Size: 400px wide, screen height - 50px
    ImGui::Begin("Objects In Scene", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Objects In Scene");
    ImGui::Separator();

    // Add content for the left menu here
    if (ImGui::BeginTabBar("Objects")) {
        if (ImGui::BeginCombo("Add Object", "Add")) {
            if (ImGui::Selectable("Cube")) {
                GameObject* cube = new GameObject(0, "", "", "");
                pos = {0, 0, 0};
                rot = {0, 0, 0};
                scale = 1.0f;
                sc->AddGameObject(cube);
            }
            if (ImGui::Selectable("Sphere")) {
                GameObject* sphere = new GameObject(0, "", "", "");
                pos = {0, 0, 0};
                rot = {0, 0, 0};
                scale = 1.0f;
                sc->AddGameObject(sphere);
            }
            if (ImGui::Selectable("Custom Model")) {
                // Open the file dialog for custom model selection
                ImGui::SetNextWindowSize(ImVec2(600, 400));
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose Model", ".obj,.fbx,.gltf");
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Remove")) {
            // Logic for removing the selected object
            if (sc->selected != nullptr) {
                sc->RemoveGameObject(sc->selected);
                sc->selected = nullptr;
            }
        }

        if (ImGui::Button("New Scene")) {
            // Logic for creating a new scene
            sc->selected = nullptr;
            sc->ClearScene();
        }
        ImGui::EndTabBar();
    }

    // Handle the file dialog for custom model selection
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

            // Create a new GameObject and load the custom model
            GameObject* customModel = new GameObject(2, filePathName, "", "");
            pos = {0, 0, 0};
            rot = {0, 0, 0};
            scale = 1.0f;
            sc->AddGameObject(customModel);
        }

        // Close the file dialog
        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::End();

    // Right Menu (unchanged)
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    ImGui::SetNextWindowPos(ImVec2(GetScreenWidth() - menuWidth, menuPos)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight)); // Size: 400px wide, screen height - 50px
    ImGui::Begin("Right Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Right Side Menu");
    ImGui::Separator();

    // Object Inspector (unchanged)
    if (ImGui::BeginTabBar("Object Inspector")) {
        if (ImGui::TabItemButton("Properties")) {}
        if (ImGui::TabItemButton("Shaders and Materials")) {}
        if (ImGui::TabItemButton("Animations")) {}
        ImGui::EndTabBar();
    }

    // Transform and other UI elements (unchanged)
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
    ImGui::Text("Current Value: %.2f", scale);
    ImGui::SliderFloat("Scale:", &scale, 0.0f, 100.0f, "Value: %.2f");
    ImGui::End();

    // Bottom Menu (unchanged)
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    ImGui::SetNextWindowPos(ImVec2(menuWidth, 750.0f)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth() - 2.0f * menuWidth, menuPos + 330.0f)); // Size: 400px wide, screen height - 50px
    ImGui::Begin("File Manager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("File Manager");
    ImGui::Separator();
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