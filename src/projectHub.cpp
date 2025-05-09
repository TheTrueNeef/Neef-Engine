#include "projectHub.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
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

using json = nlohmann::json;

ProjectNode::ProjectNode(const std::string& projectPath) : path(projectPath), next(nullptr) {}

projectHub::projectHub() : head(nullptr) {
    loadProjects();
}

projectHub::~projectHub() {
    saveProjects();
    clearProjects();
}

void projectHub::addProject(const std::string& projectPath) {
    ProjectNode* newNode = new ProjectNode(projectPath);
    newNode->next = head;
    head = newNode;
    saveProjects();
}

void projectHub::removeProject(const std::string& projectPath) {
    ProjectNode* current = head;
    ProjectNode* prev = nullptr;

    while (current) {
        if (current->path == projectPath) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            saveProjects();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void projectHub::listProjects() const {
    ProjectNode* current = head;
    while (current) {
        std::cout << current->path << std::endl;
        current = current->next;
    }
}

void projectHub::clearProjects() {
    while (head) {
        ProjectNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void projectHub::saveProjects() const {
    json j;
    ProjectNode* current = head;
    while (current) {
        j["projects"].push_back(current->path);
        current = current->next;
    }
    std::ofstream file(saveFile);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}

void projectHub::loadProjects() {
    std::ifstream file(saveFile);
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();
        if (j.contains("projects")) {
            for (const auto& path : j["projects"]) {
                addProject(path);
            }
        }
    }
}

void projectHub::newWindow(int width, int height) {
    // Use full screen
    ImGui::SetNextWindowBgAlpha(1.0f);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2((float)width + 200.0f, (float)height + 250.0f));

    ImGui::Begin("Neef Engine Project Selection", nullptr,
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::SetCursorPos(ImVec2(width * 0.05f, height * 0.05f));  // Padding
    ImGui::Text("Neef Engine Project Selection");

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.2f, 0.6f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.3f, 0.7f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.1f, 0.5f, 1.0f));

    if (ImGui::Button("New Project", ImVec2(200, 40))) {
        // TODO: Handle new project logic
    }

    ImGui::Separator();
    ImGui::Text("Recent Projects:");

    ProjectNode* current = head;
    while (current) {
        if (ImGui::Button(current->path.c_str(), ImVec2(300, 30))) {
            // TODO: Load selected project
            std::cout << "Selected project: " << current->path << std::endl;
        }
        current = current->next;
    }

    ImGui::PopStyleColor(3);
    ImGui::End();
}


