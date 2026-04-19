#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl2.h>
#include <SDL.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

int main(int, char**){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("CoConut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_GLContext gl = SDL_GL_CreateContext(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, gl);
    ImGui_ImplOpenGL2_Init();

    bool done = false;
    while(!done){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            ImGui_ImplSDL2_ProcessEvent(&e);
            if(e.type == SDL_QUIT) done = true;
        }
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("CoConut Editor Pro");
        ImGui::Text("500 Efeitos | Keyframes | Color Grading");
        ImGui::Separator();
        if(ImGui::Button("Timeline", {120,40})){}
        ImGui::SameLine();
        if(ImGui::Button("Efeitos", {120,40})){}
        ImGui::SameLine();
        if(ImGui::Button("Export", {120,40})){}
        ImGui::End();

        ImGui::Render();
        glViewport(0,0,1280,720);
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    return 0;
}
