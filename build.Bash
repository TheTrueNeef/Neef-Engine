cd src
g++ main.cpp mouse_movement.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui.cpp rlImgui.cpp -o main -L"C:/msys64/ucrt64/lib" -I"C:/msys64/ucrt64/include" -I"C:/PRJ/RaylibGame/include" -lraylib -lopengl32 -lgdi32 -lwinmm
.\main.exe