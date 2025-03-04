#ifndef PROJECTHUB_H
#define PROJECTHUB_H

#include "raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>
#include "rlImGui.h"
#include "imgui.h"
#include "imgui_impl_raylib.h"
#include "gameobject.h"
#include "Scene.h"
#include "json.hpp"
#include <cstdio>
#include "ImGuiFileDialog.h"
#include "tinyfiledialogs.h"
#include <string>
#include <fstream>

class ProjectNode {
public:
    std::string path;
    ProjectNode* next;

    ProjectNode(const std::string& projectPath);
};

class projectHub {
private:
    ProjectNode* head;
    const std::string saveFile = "projects.json";

    void saveProjects() const;
    void loadProjects();

public:
    projectHub();
    ~projectHub();

    void addProject(const std::string& projectPath);
    void removeProject(const std::string& projectPath);
    void listProjects() const;
    void clearProjects();

    void newWindow(int width, int height);
};

#endif // PROJECTHUB_H
