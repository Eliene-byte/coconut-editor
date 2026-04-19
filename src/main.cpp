#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "effects.h"
#include <vector>
#include <string>
extern "C" { const char* tinyfd_openFileDialog(const char*,const char*); }

struct Clip{ std::string file; float pos=0,dur=5; };
struct Project{ std::vector<Clip> clips; };

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* w = SDL_CreateWindow("CoConut Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    auto gl = SDL_GL_CreateContext(w);
    SDL_GL_MakeCurrent(w, gl);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION(); 
    ImGui::CreateContext(); 
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    
    ImGui_ImplSDL2_InitForOpenGL(w, gl); 
    ImGui_ImplOpenGL3_Init("#version 130");

    Project p; 
    auto fx = getEffects(); 
    int tab = 0; 
    bool run = true;
    
    while(run){
        SDL_Event e; 
        while(SDL_PollEvent(&e)){ 
            ImGui_ImplSDL2_ProcessEvent(&e); 
            if(e.type == SDL_QUIT) run = false; 
        }
        
        ImGui_ImplOpenGL3_NewFrame(); 
        ImGui_ImplSDL2_NewFrame(); 
        ImGui::NewFrame();

        ImGui::SetNextWindowPos({0,0}); 
        ImGui::SetNextWindowSize({1600,900});
        ImGui::Begin("CoConut", 0, ImGuiWindowFlags_NoDecoration);

        if(ImGui::Button("Timeline")) tab=0; ImGui::SameLine();
        if(ImGui::Button("Efeitos (500)")) tab=1; ImGui::SameLine();
        if(ImGui::Button("Textos")) tab=2; ImGui::SameLine();
        if(ImGui::Button("Cor")) tab=3; ImGui::SameLine();
        if(ImGui::Button("Export")) tab=4;

        ImGui::Separator();
        if(tab==0){
            if(ImGui::Button("Importar")){ auto f = tinyfd_openFileDialog("Video","",0,0); if(f){ p.clips.push_back({f}); } }
            for(auto& c : p.clips) ImGui::Text("%s", c.file.c_str());
        }
        if(tab==1){ 
            ImGui::BeginChild("fx");
            for(auto& e : fx) if(ImGui::Button(e.name.c_str())){} 
            ImGui::EndChild();
        }
        if(tab==2){ ImGui::Text("Textos VFX - em breve"); }
        if(tab==3){ ImGui::Text("Coloração avançada - em breve"); }
        if(tab==4){ if(ImGui::Button("Exportar MP4")){} }

        ImGui::End();
        ImGui::Render(); 
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT); 
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
        SDL_GL_SwapWindow(w);
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
