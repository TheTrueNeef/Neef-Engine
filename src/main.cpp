#include "C:/msys64/ucrt64/include/raylib.h"
#include <iostream>
#include <cstring>
#include <raymath.h>
#include "mouse_movement.h"
#include "rlImGui.h"
#include "imgui.h"
#include "imgui_impl_raylib.h"
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

void physicsHandler() {}


void gameloop()
{
}

void ShowMenuBar(ImFont* customFont, Camera3D camMain, Vector3& pos) {
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
            if (ImGui::MenuItem("\uf059 Stop", "F1")) 
            {
                // Action to stop code
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Revert style changes
    ImGui::PopStyleVar(2);
    const float menuWidth = 400.0f;
    const float menuHeight = GetScreenHeight() -50.0f;
    const float menuPos = 42.0f;
    ImGui::SetNextWindowBgAlpha(1.0f); // Set background alpha to fully opaque (1.0)
    // Left Menu
    ImGui::SetNextWindowPos(ImVec2(0, menuPos)); // Position: Top-left corner below the main menu bar
    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight)); // Size: 400px wide, screen height - 50px
    ImGui::SetWindowFontScale(10.0f); // Scale text in the current window
    ImGui::Begin("Scriptor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoDecoration);
    ImGui::Text("Scriptor");
    ImGui::Separator();
    // Add content for the left menu here
    if(ImGui::BeginTabBar("Scriptor"))
    {
        if(ImGui::TabItemButton("Fullscreen"))
        {

        }
        if(ImGui::TabItemButton("New Block Script"))
        {

        }
        if(ImGui::TabItemButton("Edit Code"))
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
    ImGui::Text("Current Value: %.2f", pos.x);
    ImGui::SliderFloat("X:", &pos.x, -100.0f, 100.0f, "Value: %.2f");
    ImGui::Text("Current Value: %.2f", pos.y);
    ImGui::SliderFloat("Y:", &pos.y, -100.0f, 100.0f, "Value: %.2f");
    ImGui::Text("Current Value: %.2f", pos.z);
    ImGui::SliderFloat("Z:", &pos.z, -100.0f, 100.0f, "Value: %.2f");
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
}


void InitializeFonts(ImFont* customFont) {
    ImGuiIO& io = ImGui::GetIO();
    customFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("../resources/fonts/aristotelica-icons-regular.ttf", 20.0f);
                if (customFont == nullptr) {
        TraceLog(LOG_ERROR, "Failed to load font!");
    } else {
        rlImGuiReloadFonts(); // Reload fonts after adding a new one
    }
    
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

#define MAX_COLUMNS 20

int main(void) {
    int screenWidth = 800;
    int screenHeight = 450;

    // Set window flags initially for transparent window
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE); 
    InitWindow(screenWidth, screenHeight, "Neef Engine V-0.0c");
    SetWindowMinSize(800,450);
    Image icon = LoadImage("../resources/neeflogo/icon.png");
    SetWindowIcon(icon);
    SetExitKey(NULL);
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
    //
    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }
    //
    // Physics
    float gravity = -9.8f; // Gravity force (downwards)
    float velocity = 0.0f; // Initial velocity
    float groundLevel = -5.0f; // Ground level (Y position of the floor)

    Texture2D topMenuBack = LoadTexture("../resources/topMenu.png");
    Texture2D LRMenuBack = LoadTexture("../resources/leftMenuBack.png");
    Texture2D botMenuBack = LoadTexture("../resources/bottomMenu.png");
    Image logoImage = LoadImage("../resources/neeflogo/neeflogo3.png");
    
    Model model = LoadModel("./resources/AllAnimalsnotOne1Point.obj");
    
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
    Vector3 posx = {0,0,0};
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
            BeginMode3D(camMain);
                //DrawPoint3D()
                //gameloop();
                DrawGrid(1000,1.0f);
                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
                DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
                DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
                DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
                }
                //DrawModel(model, {0,0,0}, 1.0f, ORANGE); // Adjust scale if needed
                //DrawModel(car2,modelPosition,10.0f,RED);
            EndMode3D();
            EndScissorMode();
            //Imgui
            ImGui_ImplRaylib_Init();
            ImGui_ImplRaylib_NewFrame();
            rlImGuiBegin();
            ShowMenuBar(customFont, camMain, posx);
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
