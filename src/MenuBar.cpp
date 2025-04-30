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
#include "tinyfiledialogs.h"
#include "PhysicsManager.h"

using json = nlohmann::json; // Alias the namespace for easier usage

std::string getMtlFilePath(const std::string& objFilePath) {
    size_t dotIndex = objFilePath.find_last_of('.');
    if (dotIndex != std::string::npos) {
        return objFilePath.substr(0, dotIndex) + ".mtl"; // Replace extension with .mtl
    }
    return objFilePath; // Return original if no extension found
}


void initColors()
{
    // Tab Button Colors
ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.35f, 0.36f, 0.35f, 1.0f));                // Default tab color (dim) - #595B5A
ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.08f, 0.76f, 0.64f, 1.0f));        // Brighter when hovered - #14C3A2
ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.05f, 0.90f, 0.66f, 1.0f));         // Slightly brighter when active - #0DE5A8
ImGui::PushStyleColor(ImGuiCol_TabUnfocused, ImVec4(0.35f, 0.36f, 0.35f, 1.0f));      // Slightly transparent when unfocused - #595B5A
ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0.05f, 0.90f, 0.66f, 1.0f)); // Active but unfocused - #0DE5A8

// Menu Item Colors
ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.08f, 0.76f, 0.64f, 1.0f));           // Default menu item color - #14C3A2
ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.05f, 0.90f, 0.66f, 1.0f));    // Highlighted when hovered - #0DE5A8
ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.49f, 0.95f, 0.60f, 1.0f));     // Slightly brighter when active - #7CF49A

// Button Colors
ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.49f, 0.95f, 0.60f, 1.0f));      // Button color - #7CF49A
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.72f, 0.99f, 0.60f, 1.0f)); // Hovered color - #B8FD99
ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.05f, 0.90f, 0.66f, 1.0f));  // Active color - #0DE5A8

// Transform and other UI elements (unchanged)
ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.49f, 0.95f, 0.60f, 1.0f));      // Button color - #7CF49A
ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.05f, 0.90f, 0.66f, 1.0f));  // Active color - #0DE5A8

// Scroll Bar Colors
ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0.35f, 0.36f, 0.35f, 1.0f)); // Background Color - #595B5A
ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.08f, 0.76f, 0.64f, 1.0f)); // #14C3A2
ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, ImVec4(0.05f, 0.90f, 0.66f, 1.0f)); // #0DE5A8
ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, ImVec4(0.49f, 0.95f, 0.60f, 1.0f)); // #7CF49A

}
void popColors()
{
    int colorsToPop = 17;
    ImGui::PopStyleColor(colorsToPop);
}
void ShowFileDialog(bool showFileDialog)
{
    if (showFileDialog)
    {
        ImGui::OpenPopup("Open File");
    }

    // Modal popup to force the file dialog to stay on top
    if (ImGui::BeginPopupModal("Open File", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        // Show file dialog
        ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey", ImGuiWindowFlags_NoCollapse);

        // If a file is selected
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            std::cout << "Selected File: " << filePath << std::endl;
            showFileDialog = false; // Close the modal
            ImGui::CloseCurrentPopup();
        }

        // If cancel is pressed
        if (!ImGuiFileDialog::Instance()->IsOpened())
        {
            showFileDialog = false; // Close the modal
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}
void MenuBar::ShowMenuBar(ImFont* customFont, Camera3D camMain, Vector3& pos, Vector3& rot, Scene* sc, float& scale, ToggleState& state, Vector3& color, 
                            PhysicsManager& phys, bool& PhysicsSimulating, bool& canCollide, bool& isStatic, float& mass, ColliderType& col) 
                            {
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
                PhysicsSimulating = true;
                phys.StartSimulation();
                std::cout << "Physics Simulation Started" << std::endl;
            }
            if (ImGui::MenuItem("Run Fullscreen (Unavailable)")) {
                // Action to show about dialog
            }
            ImGui::EndMenu();
        }

        // Stop menu
        if (ImGui::BeginMenu("Stop")) {
            if (ImGui::MenuItem("\uf059 Stop", "F1")) {
                PhysicsSimulating = false;
                phys.StopSimulation();
                std::cout << "Physics Simulation Stopped" << std::endl;
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
                cube->physics.mass = 1.0f;                // Dynamic body
                cube->physics.affectedByGravity = true;   // Gravity enabled
                sc->AddGameObject(cube);
                phys.AddObject(cube);
            }
            if (ImGui::Selectable("Sphere")) {
                GameObject* sphere = new GameObject(1, "", "", "");
                pos = {0, 0, 0};
                rot = {0, 0, 0};
                scale = 1.0f;
                sc->AddGameObject(sphere);
                phys.AddObject(sphere);

            }
            if (ImGui::Selectable("Plane")) {
                GameObject* plane = new GameObject(3, "", "", "");
                pos = {0, 0, 0};
                rot = {0, 0, 0};
                scale = 1.0f;
                sc->AddGameObject(plane);
                phys.AddObject(plane);

            }
            if (ImGui::Selectable("Custom Model")) {
                // Open the file dialog for custom model selection
                const char* filterPatterns[] = { "*.obj" }; // Only allow .obj files
                const char *filePath = tinyfd_openFileDialog("Select Model", "", 1, filterPatterns, "OBJ Files (*.obj)", 0);
                try
                {
                    if (filePath) 
                    {
                        std::string filePathName = filePath;
                        std::string mtlPath = getMtlFilePath(filePath);
                        // Create and add a new game object
                        GameObject* customModel = new GameObject(2, filePathName, mtlPath, "");
                        pos = {0, 0, 0};
                        rot = {0, 0, 0};
                        scale = 1.0f;
                        sc->AddGameObject(customModel);
                        phys.AddObject(customModel);

                    }
                }
                catch(const std::exception& e)
                {
                    std::cout << "Failed To Load File Exception 1: Report" << std::endl;
                }
                
                
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
        ImGui::SameLine();
        if (ImGui::Button("New Scene")) {
            // Logic for creating a new scene
            sc->selected = nullptr;
            sc->ClearScene();
        }
        ImGui::EndTabBar();
    }

    if (ImGui::BeginPopup("FileSelectPopup")) {
    ImGui::Text("Select a model file:");
    if (ImGui::Button("Choose File")) {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose Model", ".obj,.fbx,.gltf");
    }

    // Render the file dialog separately
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { 
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

        if (ImGui::Button("Close")) 
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    popColors();
    ImGui::End();

    
// If `ImGuiCol_TabDimmed` and `ImGuiCol_TabDimmedSelected` exist in your version of ImGui, 
// you can adjust them as well to be more subtle

    //enum ToggleState { Prop, SaM, Anim }; //Properties, Shaders and Materials, Animations
    // Object Inspector (unchanged)
        // Right Menu (unchanged)
        ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
        ImGui::SetNextWindowPos(ImVec2(GetScreenWidth() - menuWidth, menuPos)); // Position: Top-right corner below the main menu bar
        ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight)); // Size: 400px wide, screen height - 50px
        initColors();
        ImGui::Begin("Right Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
        ImGui::Text("Right Side Menu");
        ImGui::Separator();
        if (ImGui::BeginTabBar("Object Inspector")) {
            if (ImGui::TabItemButton("Properties")) {state = ToggleState::Prop;}
            if (ImGui::TabItemButton("Shaders and Materials")) {state = ToggleState::SaM;}
            if (ImGui::TabItemButton("Animations")) {state = ToggleState::Anim;}
            ImGui::EndTabBar();
        }
    const char* shapeOptions[] = { "Box", "Sphere", "Capsule", "Cylinder", "Cone", "Plane", "None" };
    static int selectedShape = 0;
    switch (state)
    {
    case ToggleState::Prop:
        ImGui::Text("Vector Space Position and Rotation");
        char coordinates[50];
        sprintf(coordinates, "X: %.2f, Y: %.2f, Z: %.2f", camMain.position.x, camMain.position.y, camMain.position.z);
        char target[50];
        sprintf(target, "X: %.2f, Y: %.2f, Z: %.2f", camMain.target.x, camMain.target.y, camMain.target.z);
        ImGui::Text(coordinates);
        ImGui::Text(target);
        ImGui::Separator();
        ImGui::Text("Object Transform");
            //ImGui::SameLine();
            //ImGui::PushItemWidth(100); // Locks the width of the slider
        ImGui::SliderFloat("X:", &pos.x, -100.0f, 100.0f, "Value: %.2f");
        // ImGui::Text("%.2f", pos.x);
        //         ImGui::PopItemWidth(); // Restore previous width
        //     ImGui::SameLine();
        //     ImGui::PushItemWidth(100); // Locks the width of the slider
        ImGui::SliderFloat("Y:", &pos.y, -100.0f, 100.0f, "Value: %.2f");
        // ImGui::Text("%.2f", pos.y);
        //         ImGui::PopItemWidth(); // Restore previous width
        //     ImGui::SameLine();
        //     ImGui::PushItemWidth(100); // Locks the width of the slider
        ImGui::SliderFloat("Z:", &pos.z, -100.0f, 100.0f, "Value: %.2f");
        // ImGui::Text("%.2f", pos.z);
        //         ImGui::PopItemWidth(); // Restore previous width
        // ImGui::Separator();
        ImGui::Text("Object Rotation");
            // ImGui::SameLine();
            // ImGui::PushItemWidth(100); // Locks the width of the slider
        ImGui::SliderFloat("Pitch:", &rot.x, -360.0f, 360.0f, "Value: %.2f");
        // ImGui::Text("%.2f", rot.x);
        //         ImGui::PopItemWidth(); // Restore previous width
        //     ImGui::SameLine();
        //     ImGui::PushItemWidth(100); // Locks the width of the slider
        ImGui::SliderFloat("Yaw:", &rot.y, -360.0f, 360.0f, "Value: %.2f");
        // ImGui::Text("%.2f", rot.y);
        //         ImGui::PopItemWidth(); // Restore previous width
        //     ImGui::SameLine();
        //     ImGui::PushItemWidth(100); // Locks the width of the slider
        ImGui::SliderFloat("Roll:", &rot.z, -360.0f, 360.0f, "Value: %.2f");
        // ImGui::Text("%.2f", rot.z);
        //         ImGui::PopItemWidth(); // Restore previous width
        ImGui::Separator();
            // ImGui::SameLine();
            // ImGui::PushItemWidth(100); // Locks the width of the slider
            ImGui::Text("Object Scale");
        ImGui::SliderFloat("Scale:", &scale, 0.0f, 100.0f, "Value: %.2f");
        // ImGui::Text("%.2f", scale);
                // ImGui::PopItemWidth(); // Restore previous width
        ImGui::Separator();
            ImGui::Text("Physical Properties");
        ImGui::SliderFloat("Mass:", &mass, 0.0f, 100.0f, "Value: %.2f");
        ImGui::Checkbox("Collider", &canCollide);
        ImGui::SameLine();
        ImGui::Dummy(ImVec2(20, 0));  // Add horizontal space
        ImGui::SameLine();
        ImGui::Checkbox("Effected by Gravity", &isStatic);

        if (ImGui::Combo("Collider Shape", &selectedShape, shapeOptions, IM_ARRAYSIZE(shapeOptions))) 
        {
            col = static_cast<ColliderType>(selectedShape);
        }
        break;
    case ToggleState::SaM:
    {
        // Advanced RGB color picker
        float cols[3] = {color.x, color.y, color.z};
        ImGui::ColorPicker3("Pick a Color", cols);
        //std::cout << cols[0]<<cols[1]<<cols[2] << std::endl;
        color = {cols[0],cols[1],cols[2]};
    }
        break;
    default:
        break;
    }
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
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y)); // Size: Windox.x, screen height - Windox.y
    ImGui::Begin("Neef Engine Project Selection", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Neef Engine Project Selection");
        // Start an ImGui window for project selection
    ImGui::Begin("Project Selection", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
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
    ImGui::PopFont();
    ImGui::End();
    ImGui::Separator();
    ImGui::Text("Option A");
    ImGui::Text("Option B");
    ImGui::Text("Option C");
    ImGui::End();
}