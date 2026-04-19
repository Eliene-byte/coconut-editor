#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl2.h>
#include <GL/gl.h>

int main(int, char**) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("CoConut Editor", 100, 100, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(win, ctx);
    ImGui_ImplOpenGL2_Init();
    
    bool run = true;
    while(run) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if(e.type == SDL_QUIT) run = false;
        }
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("CoConut");
        ImGui::Text("Build funcionando!");
        ImGui::End();
        
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(win);
    }
    return 0;
}
