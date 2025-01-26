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
#include "MenuBar.h"
using json = nlohmann::json; // Alias the namespace for easier usage

/*
#
    g++ main.cpp mouse_movement.cpp -o main -L"C:/msys64/ucrt64/lib" -I"C:/msys64/ucrt64/include" -lraylib -lopengl32 -lgdi32 -lwinmm
#
*/

#define FRAME_COUNT 28  // Total number of frames
#define FRAME_DELAY 0.04f // Delay per frame in seconds

void InitializeFonts(ImFont* customFont) {
    ImGuiIO& io = ImGui::GetIO();
    customFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("resources/fonts/aristotelica-icons-regular.ttf", 20.0f);
                if (customFont == nullptr) {
        TraceLog(LOG_ERROR, "Failed to load font!");
    } else {
        rlImGuiReloadFonts(); // Reload fonts after adding a new one
    }
}

void userInputHandler(bool &menuFLag, bool &refMenu, Camera3D &cam, float &mveAmount) 
{
    if (IsKeyPressed(KEY_ENTER) && !menuFLag) {
        refMenu = false;
        menuFLag = !menuFLag;
         int screenWidth = GetMonitorWidth(0);
        int screenHeight = GetMonitorHeight(0);

        // Adjust the window size to fit the screen dimensions
        SetWindowSize(screenWidth, screenHeight);

        // Ensure the window is positioned at the top-left corner
        SetWindowPosition(0,30);
        SetWindowState(FLAG_WINDOW_MAXIMIZED);
        SetWindowFocused();

        // Ensure the window has decorations (borders, title bar, etc.)
        ClearWindowState(FLAG_FULLSCREEN_MODE);
        ClearWindowState(FLAG_WINDOW_UNDECORATED);

    }
}

#define MAX_COLUMNS 20

int main(void) {
    int screenWidth = 800;
    int screenHeight = 450;

    // Set window flags initially for transparent window
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT); 
    InitWindow(screenWidth, screenHeight, "Neef Engine V-0.0f");
    SetWindowMinSize(800,450);
    Image icon = LoadImage("resources/neeflogo/icon.png");
    SetWindowIcon(icon);
    SetExitKey(KEY_B && KEY_A);
    // Camera setup
    Camera3D camMain = {0};
    camMain.position = (Vector3){0.0f, 10.0f, 10.0f}; // Camera position
    camMain.target = (Vector3){0.0f, 1.0f, 0.0f};  // Looking at origin
    camMain.up = (Vector3){0.0f, 1.0f, 0.0f};      // Up vector
    camMain.fovy = 60.0f; // Field of view (in degrees)
    camMain.projection = CAMERA_PERSPECTIVE; // Camera projection type
    camMain.position.x = Clamp(camMain.position.x, -200, 200);
    camMain.position.y = Clamp(camMain.position.y, -200, 200);
    camMain.position.z = Clamp(camMain.position.z, -200, 200);
    // Sensitivity for camera rotation
    float sensitivity = 0.1f;
    
    // Physics
    float gravity = -9.8f; // Gravity force (downwards)
    float velocity = 0.0f; // Initial velocity
    float groundLevel = -5.0f; // Ground level (Y position of the floor)

    Texture2D topMenuBack = LoadTexture("resources/topMenu.png");
    Texture2D LRMenuBack = LoadTexture("resources/leftMenuBack.png");
    Texture2D botMenuBack = LoadTexture("resources/bottomMenu.png");
    Image logoImage = LoadImage("resources/neeflogo/neeflogo3.png");
    //
    Scene scene("TemplateScene");
    MenuBar guiMENU;
    //

    float pitch = 0.0f;
    float roll = 0.0f;
    float yaw = 0.0f;

    Vector3 rotation = {0.0f,0.0f,0.0f}; // x: pitch, y: roll, z: yaw

    //
    ImageResize(&logoImage,logoImage.width/70,logoImage.height/70);
    Texture2D logoTexture = LoadTextureFromImage(logoImage);
    Texture2D frames[FRAME_COUNT];
    for (int i = 0; i < FRAME_COUNT; i++) {
        char fileName[64];
        snprintf(fileName, sizeof(fileName), "resources/loading/frame_%02d_delay-0.04s.png", i); // Updated file naming
        frames[i] = LoadTexture(fileName);

        if (frames[i].id == 0) {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", fileName);
        }
    }

    //init ImgGUI
    rlImGuiSetup(true);
    ImFont* customFont = nullptr;
    //InitializeFonts(customFont); // Load the custom font
    
    bool show_demo_window = true;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float timer = 0.0f;
    bool showWhiteBackground = false;  // Flag to control the background color change
    bool displaySphere = true;  // Flag to control sphere rendering
    bool inGame = false;
    SetTargetFPS(60);
    bool mouseMovementEnabled = false;

    //temp
    Vector3 position = {0,0,0};
    while (!WindowShouldClose()) {


        // Gameplay
        float move = 1.0f;
        if(inGame) {move = 0.5f;}
        else {move = 0.0f;}
        userInputHandler(inGame, showWhiteBackground, camMain, move);
        

        // Update animation frames
        frameTimer += GetFrameTime();
        if (frameTimer >= FRAME_DELAY && !inGame) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % FRAME_COUNT; // Loop through frames
        }

        // Track time for menu
        timer += GetFrameTime();
        if (timer >= 2.5f && !showWhiteBackground && !inGame) {
            showWhiteBackground = true;  // Change to white background
            displaySphere = false;  // Stop displaying the sphere
            SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED); // Default window flags
            SetWindowFocused();
            SetWindowSize(1000, 700);
        }

        // Start drawing
        BeginDrawing();
        if (showWhiteBackground) {
            ClearBackground(DARKGRAY);  
            ClearWindowState(FLAG_FULLSCREEN_MODE);
            ClearWindowState(FLAG_WINDOW_UNDECORATED);
            DrawText("PRESS \"ENTER\" TO START...", 0, 80, 40, WHITE);
            DrawText("Neef Engine Development kit\nDeveloper build V 0.0-f1", 0, 0, 10, WHITE);
            DrawText("x", 1892, 0, 40, RED);
            DrawLine(1880, 0, 1880, 40, RED);
            DrawLine(1880, 40, 1920, 40, RED);
        } else if (inGame) {
            if (IsKeyPressed(KEY_M)) {

                mouseMovementEnabled = !mouseMovementEnabled;
            }
            
        // Update camera based on mouse movement if enabled
            if (mouseMovementEnabled) {
                UpdateMouseMovement(&camMain);
                HideCursor(); // Hide the system mouse cursor
                } else {
                ShowCursor(); // Show the system mouse cursor
            }
            ClearBackground(DARKGRAY);
            ClearWindowState(FLAG_WINDOW_UNDECORATED);
            
            screenHeight = GetScreenHeight();
        
            
            //Background
            DrawTexture(LRMenuBack,0,0,WHITE);
            DrawTexture(LRMenuBack,1520,0,WHITE);
            DrawTexture(botMenuBack,400,750,WHITE);
            DrawTexture(topMenuBack,0,0,WHITE);
            
            DrawTexture(logoTexture, 5, 5, WHITE);
            DrawFPS(1540,95);
            BeginScissorMode(400,30,1120,720);
            //apply transformations
            if(scene.selected != nullptr)
            {
                scene.selected->isSelected = true;
                scene.selected->SetPosition(position);
                scene.selected->SetRotation(rotation);
            }
            BeginMode3D(camMain);
                scene.Update();
                scene.Draw();
            EndMode3D();

            
            EndScissorMode();
            //Imgui
            ImGui_ImplRaylib_Init();
            ImGui_ImplRaylib_NewFrame();
            rlImGuiBegin();
            //ShowMenuBar(customFont, camMain, position, rotation);
            guiMENU.ShowMenuBar(customFont, camMain, position, rotation, &scene);
            rlImGuiEnd();
        } else {
            ClearBackground(BLANK);  // Transparent background initially
        }

        if (displaySphere) {
            Texture2D currentTexture = frames[currentFrame];
            float scaledWidth = currentTexture.width * 3.0f;
            float scaledHeight = currentTexture.height * 3.0f;
            Rectangle destRect = { 
                (screenWidth - scaledWidth) / 2, 
                (screenHeight - scaledHeight) / 2, 
                scaledWidth, 
                scaledHeight 
            };
            DrawTexturePro(currentTexture, 
                           (Rectangle){ 0, 0, (float)currentTexture.width, (float)currentTexture.height },
                           destRect, 
                           (Vector2){ 0, 0 }, 
                           0.0f, 
                           WHITE);
        }

        EndDrawing();
    }

    //UnloadModel(model);


    //unload imgui
    rlImGuiShutdown();

    //Unload loading screen
    for (int i = 0; i < FRAME_COUNT; i++) {
        UnloadTexture(frames[i]);
    }
    scene.ClearScene();
    CloseWindow();
    //Delete pointers
    delete customFont;
    customFont = nullptr;

    
    return 0;
}
