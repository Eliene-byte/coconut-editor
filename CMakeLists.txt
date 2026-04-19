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


# --- ImGui backends (arquivos locais, vcpkg não instala mais)
find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui SDL2::SDL2 SDL2::SDL2main)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui_backends/imgui_impl_sdl2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui_backends/imgui_impl_opengl3.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui_backends
)
