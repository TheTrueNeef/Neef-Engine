#include "C:/msys64/ucrt64/include/raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>
#include "mouse_movement.h"
#include "C:/PRJ/RaylibGame/include/rlImGui.h"
#include "C:/PRJ/RaylibGame/include/imgui.h"


/*
#
    g++ main.cpp mouse_movement.cpp -o main -L"C:/msys64/ucrt64/lib" -I"C:/msys64/ucrt64/include" -lraylib -lopengl32 -lgdi32 -lwinmm
#
*/

#define FRAME_COUNT 28  // Total number of frames
#define FRAME_DELAY 0.04f // Delay per frame in seconds

Vector3 GetCameraForward(Camera camera) {
    Vector3 forward = Vector3Subtract(camera.target, camera.position);
    return Vector3Normalize(forward);  // Normalize to ensure consistent movement speed
}

// Function to get the normalized right direction of the camera
Vector3 GetCameraRight(Camera camera) {
    Vector3 forward = GetCameraForward(camera);  // Get the forward direction
    Vector3 right = Vector3CrossProduct(camera.up, forward);  // Perpendicular vector
    return Vector3Normalize(right);  // Normalize to ensure consistent movement speed
}

// Function to get the normalized up direction of the camera
Vector3 GetCameraUp(Camera camera) {
    Vector3 forward = GetCameraForward(camera);  // Get the forward direction
    Vector3 up = Vector3CrossProduct(forward, GetCameraRight(camera));  // Perpendicular vector
    return Vector3Normalize(up);  // Normalize to ensure consistent movement speed
}

void userInputHandler(bool &menuFLag, bool &refMenu, Camera3D &cam, float &mveAmount) 
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (GetMouseX() >= GetScreenWidth() - 40 && GetMouseY() <= 40) {
            CloseWindow();
        }
    }
    if (IsKeyPressed(KEY_ENTER) && !menuFLag) {
        refMenu = false;
        menuFLag = !menuFLag;
         int screenWidth = GetMonitorWidth(0);
        int screenHeight = GetMonitorHeight(0);

        // Adjust the window size to fit the screen dimensions
        SetWindowSize(screenWidth, screenHeight);

        // Ensure the window is positioned at the top-left corner
        SetWindowPosition(0,30);

        // Ensure the window has decorations (borders, title bar, etc.)
        ClearWindowState(FLAG_FULLSCREEN_MODE);
        ClearWindowState(FLAG_WINDOW_UNDECORATED);

    }
    
    Vector3 moveDirection = { 0.0f, 0.0f, 0.0f };

    Vector3 forward = GetCameraForward(cam);
    Vector3 right = GetCameraRight(cam);
    Vector3 up = GetCameraUp(cam);

    if (IsKeyDown(KEY_W)) moveDirection = Vector3Add(moveDirection, forward);   // Move forward
    if (IsKeyDown(KEY_S)) moveDirection = Vector3Subtract(moveDirection, forward); // Move backward
    if (IsKeyDown(KEY_A)) moveDirection = Vector3Add(moveDirection, right); // Move left
    if (IsKeyDown(KEY_D)) moveDirection = Vector3Subtract(moveDirection, right);   // Move right
    if (IsKeyDown(KEY_SPACE)) moveDirection = Vector3Add(moveDirection, up);   // Move up
    if (IsKeyDown(KEY_LEFT_SHIFT)) moveDirection = Vector3Subtract(moveDirection, up); // Move down


    cam.position = Vector3Add(cam.position, moveDirection);
    cam.target = Vector3Add(cam.target, moveDirection);

}

void physicsHandler() {}

void drawGrid()
{
    Vector3 strtPos={100,100,0};
    Vector3 endPos={100,-100,0};
    for(int x = 0; x < 100; x++)
    {
        DrawLine3D(strtPos, endPos, RED);
        strtPos.z += 1.0f;
        endPos.z += 1.0f;
    }
}

void gameloop()
{
    // Sphere
    Vector3 planePos = {0.0f, -1.0f, 0.0f};  // Initial position of the sphere
    Vector2 planeSize = {100.0f,100.0f};  // Radius of the sphere
    Color planeColor = GRAY;
    DrawPlane(planePos,planeSize,planeColor); // Draw the sphere at its current position
}
int main(void) {
    int screenWidth = 800;
    int screenHeight = 450;

    // Set window flags initially for transparent window
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT | FLAG_VSYNC_HINT); 
    InitWindow(screenWidth, screenHeight, "Neef Engine V-0.0a");

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
    //DisableCursor(); // Lock cursor for camera control

    // Physics
    float gravity = -9.8f; // Gravity force (downwards)
    float velocity = 0.0f; // Initial velocity
    float groundLevel = -5.0f; // Ground level (Y position of the floor)

    Texture2D topMenuBack = LoadTexture("../resources/topMenu.png");
    Texture2D LRMenuBack = LoadTexture("../resources/leftMenuBack.png");
    Texture2D botMenuBack = LoadTexture("../resources/bottomMenu.png");
    Image logoImage = LoadImage("../resources/neeflogo/neeflogo3.png");
    ImageResize(&logoImage,logoImage.width/70,logoImage.height/70);
    Texture2D logoTexture = LoadTextureFromImage(logoImage);
    Texture2D frames[FRAME_COUNT];
    for (int i = 0; i < FRAME_COUNT; i++) {
        char fileName[64];
        snprintf(fileName, sizeof(fileName), "../resources/loading/frame_%02d_delay-0.04s.png", i); // Updated file naming
        frames[i] = LoadTexture(fileName);

        if (frames[i].id == 0) {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", fileName);
        }
    }

    //Model model = LoadModel("../resources/models/Low-Poly-Racing-Car.obj");
    //Model car2 = LoadModel("../resources/models/game_house_environement.obj");
    Vector3 modelPosition = { 0.0f, 0.0f, 0.0f }; // Replace with desired position

    //init ImgGUI
    rlImGuiSetup(true);
    bool show_demo_window = true;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float timer = 0.0f;
    bool showWhiteBackground = false;  // Flag to control the background color change
    bool displaySphere = true;  // Flag to control sphere rendering
    bool inGame = false;
    SetTargetFPS(60);
    bool mouseMovementEnabled = false;
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
            DrawText("PHYSICS RENDERING COMPILATION EDITOR \nV 0.0-a", 0, 0, 10, WHITE);
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
            ClearBackground(SKYBLUE);
            ClearWindowState(FLAG_WINDOW_UNDECORATED);
            
            screenHeight = GetScreenHeight();
        
            
            //Background
            DrawTexture(LRMenuBack,0,0,WHITE);
            DrawTexture(LRMenuBack,1520,0,WHITE);
            DrawTexture(botMenuBack,400,750,WHITE);
            DrawTexture(topMenuBack,0,0,WHITE);
            //Cordinates
            char coordinates[50];
            sprintf(coordinates, "X: %.2f, Y: %.2f, Z: %.2f", camMain.position.x, camMain.position.y, camMain.position.z);
            DrawText(coordinates,1540,50,20,DARKGRAY);

            char target[50];
            sprintf(target, "X: %.2f, Y: %.2f, Z: %.2f", camMain.target.x, camMain.target.y, camMain.target.z);
            DrawText(target,1540,75,20,DARKGRAY);
            DrawTexture(logoTexture, 5, 5, WHITE);
            DrawFPS(1540,95);
            BeginScissorMode(400,30,1120,720);

            BeginMode3D(camMain);
                gameloop();
                drawGrid();
                DrawGrid(100,1.5f);
                //DrawModel(model, modelPosition, 1.0f, ORANGE); // Adjust scale if needed
                //DrawModel(car2,modelPosition,10.0f,RED);
            EndMode3D();
            EndScissorMode();
            //Imgui
        
            rlImGuiBegin();
            ImGui::ShowDemoWindow(&show_demo_window);
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
    CloseWindow();

    return 0;
}
