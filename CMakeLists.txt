cmake_minimum_required(VERSION 3.20)
project(CoConutEditor CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(CoConutEditor src/main.cpp)

target_link_libraries(CoConutEditor PRIVATE 
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2main>,SDL2::SDL2main,SDL2::SDL2main-static>
    imgui::imgui
    OpenGL::GL
)
