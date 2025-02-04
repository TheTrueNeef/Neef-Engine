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
<<<<<<< Updated upstream
=======

void initColors()
{
    // Tab Button Colors
    ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.2f, 0.2f, 0.3f, 1.0f));                // Default tab color (dim)
    ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.4f, 0.4f, 0.7f, 1.0f));        // Brighter when hovered
    ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.3f, 0.3f, 0.5f, 1.0f));         // Slightly brighter when active
    ImGui::PushStyleColor(ImGuiCol_TabUnfocused, ImVec4(0.2f, 0.2f, 0.3f, 0.8f));      // Slightly transparent when unfocused
    ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0.3f, 0.3f, 0.5f, 0.8f)); // Active but unfocused
    // Menu Item Colors
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.35f, 1.0f));           // Default menu item color
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.4f, 0.4f, 0.7f, 1.0f));     // Highlighted when hovered
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.3f, 0.3f, 0.55f, 1.0f));     // Slightly brighter when active
    // Button Colors
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.2f, 0.6f, 1.0f));      // Button color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.3f, 0.7f, 1.0f)); // Hovered color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.1f, 0.5f, 1.0f));  // Active color
    // Transform and other UI elements (unchanged)
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.4f, 0.2f, 0.6f, 1.0f));      // Button color
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.3f, 0.1f, 0.5f, 1.0f));  // Active color   
    // Scroll Bar Colors
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Background Color
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.4f, 0.2f, 0.6f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, ImVec4(0.5f, 0.3f, 0.7f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, ImVec4(0.3f, 0.1f, 0.5f, 1.0f));
}
void popColors()
{
    int colorsToPop = 17;
    ImGui::PopStyleColor(colorsToPop);
}
>>>>>>> Stashed changes
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
    //INITIALIZE COLORS
    initColors();
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
    popColors();
    
    const float menuWidth = 400.0f;
    const float menuHeight = GetScreenHeight() - 50.0f;
    const float menuPos = 42.0f;
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    //INITIALIZE COLORS
    initColors();
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
                std::cout << "Selected Custom Model" << std::endl;
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
    // Render the file dialog separately
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
    {
        std::cout << "WORKING" << std::endl;
        if (ImGuiFileDialog::Instance()->IsOk()) 
        { 
            // Get the file path
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

            // Create and add a new game object
            GameObject* customModel = new GameObject(2, filePathName, "", "");
            pos = {0, 0, 0};
            rot = {0, 0, 0};
            scale = 1.0f;
            sc->AddGameObject(customModel);
        }
    // Close the file dialog
    ImGuiFileDialog::Instance()->Close();
    }
    popColors();
    ImGui::End();

    // Right Menu (unchanged)
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    ImGui::SetNextWindowPos(ImVec2(GetScreenWidth() - menuWidth, menuPos)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight)); // Size: 400px wide, screen height - 50px
    initColors();
    ImGui::Begin("Right Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Right Side Menu");
    ImGui::Separator();
// If `ImGuiCol_TabDimmed` and `ImGuiCol_TabDimmedSelected` exist in your version of ImGui, 
// you can adjust them as well to be more subtle


    // Object Inspector (unchanged)
    if (ImGui::BeginTabBar("Object Inspector")) {
        if (ImGui::TabItemButton("Properties")) {}
        if (ImGui::TabItemButton("Shaders and Materials")) {}
        if (ImGui::TabItemButton("Animations")) {}
        ImGui::EndTabBar();
    }

    
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
    popColors();
    ImGui::End();

    // Bottom Menu (unchanged)
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    ImGui::SetNextWindowPos(ImVec2(menuWidth, 750.0f)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth() - 2.0f * menuWidth, menuPos + 330.0f)); // Size: 400px wide, screen height - 50px
    initColors();
    ImGui::Begin("File Manager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("File Manager");
    ImGui::Separator();
    ImGui::Text("Option A");
    ImGui::Text("Option B");
    ImGui::Text("Option C");
    popColors();
    ImGui::End();

    // Revert to default font if custom font was used
    if (customFont) {
        ImGui::PopFont();
    }    
}

void MenuBar::ProjSelect(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot,Scene* sc, float& scale)
{
    

    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(600, 1000)); // Size: 400px wide, screen height - 50px
    ImGui::Begin("Neef Engine Project Selection", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Neef Engine Project Selection");
        // Start an ImGui window for project selection
    ImGui::Begin("Project Selection", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.2f, 0.6f, 1.0f));      // Button color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.3f, 0.7f, 1.0f)); // Hovered color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.1f, 0.5f, 1.0f));  // Active color
    ImGui::PushFont(customFont);
    // Example: Display buttons for different projects
    if (ImGui::Button("Project 1", ImVec2(200, 50)))
    {
        //*scene = 1; // Set the scene to Project 1
        ClearWindowState(FLAG_FULLSCREEN_MODE);
        ClearWindowState(FLAG_WINDOW_UNDECORATED);
    }

    if (ImGui::Button("Project 2", ImVec2(200, 50)))
    {
        //*scene = 2; // Set the scene to Project 2
        ClearWindowState(FLAG_FULLSCREEN_MODE);
        ClearWindowState(FLAG_WINDOW_UNDECORATED);
    }

    if (ImGui::Button("Exit", ImVec2(200, 50)))
    {
        
    }
    ImGui::PopStyleColor(3);
<<<<<<< Updated upstream
}

void MenuBar::ProjSelect(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot,Scene* sc, float& scale)
{
    // Start an ImGui window for project selection
    ImGui::Begin("Project Selection", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::PushFont(customFont);

    // Example: Display buttons for different projects
    if (ImGui::Button("Project 1", ImVec2(200, 50)))
    {
        //*scene = 1; // Set the scene to Project 1
        ClearWindowState(FLAG_FULLSCREEN_MODE);
        ClearWindowState(FLAG_WINDOW_UNDECORATED);
    }

    if (ImGui::Button("Project 2", ImVec2(200, 50)))
    {
        //*scene = 2; // Set the scene to Project 2
        ClearWindowState(FLAG_FULLSCREEN_MODE);
        ClearWindowState(FLAG_WINDOW_UNDECORATED);
    }

    if (ImGui::Button("Exit", ImVec2(200, 50)))
    {
        //*scene = -1; // Exit the project selection menu
        //ProjectSelectionMenu = false;
    }

    ImGui::PopFont();
    ImGui::End();

    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f)); // Position: Top-right corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(400, 600)); // Size: 400px wide, screen height - 50px
    ImGui::Begin("File Manager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("File Manager");
=======
    ImGui::PopFont();
    ImGui::End();

>>>>>>> Stashed changes
    ImGui::Separator();
    ImGui::Text("Option A");
    ImGui::Text("Option B");
    ImGui::Text("Option C");
    ImGui::End();
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
