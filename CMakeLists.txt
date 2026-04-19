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

# --- ImGui SDL2 + OpenGL3 backends (vcpkg não fornece mais via feature)
find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui SDL2::SDL2 SDL2::SDL2main)

target_sources(${PROJECT_NAME} PRIVATE
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/imgui/backends/imgui_impl_sdl2.cpp
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/imgui/backends
)
