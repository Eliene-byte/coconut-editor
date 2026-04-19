cmake_minimum_required(VERSION 3.20)
project(CoConutEditor)

set(CMAKE_CXX_STANDARD 17)

# Baixa dependências automaticamente
include(FetchContent)

# SDL2
FetchContent_Declare(SDL2 URL https://github.com/libsdl-org/SDL/releases/download/release-2.30.0/SDL2-devel-2.30.0-VC.zip)
FetchContent_MakeAvailable(SDL2)

# ImGui
FetchContent_Declare(imgui URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.9.zip)
FetchContent_MakeAvailable(imgui)

# FFmpeg (Windows)
set(FFMPEG_DIR "${CMAKE_SOURCE_DIR}/third_party/ffmpeg")

# Inclui
include_directories(${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
include_directories(${SDL2_SOURCE_DIR}/include)
include_directories(${FFMPEG_DIR}/include)

# Arquivos
file(GLOB IMGUI_SRC ${imgui_SOURCE_DIR}/*.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp)

add_executable(CoConutEditor 
    src/main.cpp
    ${IMGUI_SRC}
)

target_link_libraries(CoConutEditor 
    ${SDL2_SOURCE_DIR}/lib/x64/SDL2.lib
    ${SDL2_SOURCE_DIR}/lib/x64/SDL2main.lib
    opengl32
)
