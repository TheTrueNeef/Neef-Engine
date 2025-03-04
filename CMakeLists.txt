# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(neef-engine VERSION 1.0)

# Specify the C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sets build type if not set by now
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(default_build_type Debug)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Add source files for your project
set(SOURCES
    src/GameObject.cpp
    src/main.cpp
    src/MenuBar.cpp
    src/mouse_movement.cpp
    src/Scene.cpp
    src/projectHub.cpp
)

# Add source files for dependencies
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)

set(RLIMGUI_SOURCES
    rlImGui/rlImGui.cpp
)

# Add ImGuiFileDialog sources (if applicable)
set(IMGUIFILEDIALOG_SOURCES
    src/ImGuiFileDialog.cpp
)

set(TINYFILEDIALOGS_SOURCES
    tinyfiledialogs/tinyfiledialogs.c
)

# Combine all sources
set(ALL_SOURCES
    ${SOURCES}
    ${IMGUI_SOURCES}
    ${RLIMGUI_SOURCES}
    ${IMGUIFILEDIALOG_SOURCES}
    ${TINYFILEDIALOGS_SOURCES}
)

# Create an executable
add_executable(neef-engine ${ALL_SOURCES})

# Add include directories for specific targets
target_include_directories(neef-engine PRIVATE
    include
    json/include/nlohmann
    imgui
    raylib/include  # Path to raylib.h
    rlImGui
    src  # For ImGuiFileDialog
    tinyfiledialogs  # File Dialog

)

# Link against the prebuilt Raylib library
if(WIN32)
    target_link_libraries(neef-engine PRIVATE ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
endif()

# Link required system libraries
if(WIN32)
    target_link_libraries(neef-engine PRIVATE opengl32 gdi32 winmm)
elseif(UNIX)
    target_link_libraries(neef-engine PRIVATE GL m pthread dl)
endif()

# Add resources directory (if needed)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/resources)

# Print the flags for the user
if (DEFINED CMAKE_BUILD_TYPE)
    message(STATUS "Generated build type: ${CMAKE_BUILD_TYPE}")
else ()
    message(STATUS "Generated config types: ${CMAKE_CONFIGURATION_TYPES}")
endif ()

message(STATUS "Compiling with the flags:")
message(STATUS "  PLATFORM=" ${PLATFORM_CPP})
message(STATUS "  GRAPHICS=" ${GRAPHICS})