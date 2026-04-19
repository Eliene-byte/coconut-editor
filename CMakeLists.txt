cmake_minimum_required(VERSION 3.20)
project(CoConutEditor)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(CoConutEditor src/main.cpp)

target_link_libraries(CoConutEditor PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    imgui::imgui
    OpenGL::GL
)
