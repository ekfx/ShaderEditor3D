cmake_minimum_required(VERSION 3.15)
project(LabX3 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

################################################################################


find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

################################################################################

add_library(glad STATIC
    third_party/src/glad.c
)
target_include_directories(glad PUBLIC
    third_party/include
)

add_library(imgui STATIC
    third_party/src/imgui/imgui.cpp
    third_party/src/imgui/imgui_draw.cpp
    third_party/src/imgui/imgui_widgets.cpp
    third_party/src/imgui/imgui_tables.cpp
    third_party/src/imgui/imgui_demo.cpp
    third_party/src/imgui/imgui_impl_glfw.cpp
    third_party/src/imgui/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    third_party/include
    third_party/include/imgui
)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

################################################################################

# I delete the folders and cmake files before compile again every time I start the pc.
file(GLOB PROJECT_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
    -freflection
    -fno-exceptions
)

target_include_directories(${PROJECT_NAME} PRIVATE BEFORE
    include
    third_party/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    imgui
    glfw
    glm::glm
    assimp::assimp
    OpenGL::GL
    Threads::Threads
)

if(WIN32)
  target_link_options(${PROJECT_NAME} PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
endif()
