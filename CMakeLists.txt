# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(neef-engine VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(default_build_type Debug)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Main source files
set(SOURCES
    src/GameObject.cpp
    src/main.cpp
    src/MenuBar.cpp
    src/mouse_movement.cpp
    src/Scene.cpp
    src/projectHub.cpp
    src/PhysicsManager.cpp
)

# Dependencies
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)

set(RLIMGUI_SOURCES rlImGui/rlImGui.cpp)
set(IMGUIFILEDIALOG_SOURCES src/ImGuiFileDialog.cpp)
set(TINYFILEDIALOGS_SOURCES tinyfiledialogs/tinyfiledialogs.c)

# Bullet Physics source files
file(GLOB_RECURSE BULLET_SOURCES
    physics/src/BulletCollision/*.cpp
    physics/src/BulletDynamics/*.cpp
    physics/src/LinearMath/*.cpp
)

# All sources combined
set(ALL_SOURCES
    ${SOURCES}
    ${IMGUI_SOURCES}
    ${RLIMGUI_SOURCES}
    ${IMGUIFILEDIALOG_SOURCES}
    ${TINYFILEDIALOGS_SOURCES}
    ${BULLET_SOURCES}
)

# Create executable
add_executable(neef-engine ${ALL_SOURCES})

# Include directories
target_include_directories(neef-engine PRIVATE
    include
    json/include/nlohmann
    imgui
    raylib/include
    rlImGui
    src
    tinyfiledialogs

    # Bullet headers
    physics/src
    physics/src/BulletCollision
    physics/src/BulletDynamics
    physics/src/LinearMath
)

# Link Raylib and system libraries
if(WIN32)
    target_link_libraries(neef-engine PRIVATE ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
    target_link_libraries(neef-engine PRIVATE opengl32 gdi32 winmm)
elseif(UNIX)
    target_link_libraries(neef-engine PRIVATE GL m pthread dl)
endif()

# Copy resources folder to build directory
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/resources)

# Print config
if (DEFINED CMAKE_BUILD_TYPE)
    message(STATUS "Generated build type: ${CMAKE_BUILD_TYPE}")
else ()
    message(STATUS "Generated config types: ${CMAKE_CONFIGURATION_TYPES}")
endif ()

message(STATUS "Compiling with the flags:")
message(STATUS "  PLATFORM=" ${PLATFORM_CPP})
message(STATUS "  GRAPHICS=" ${GRAPHICS})
