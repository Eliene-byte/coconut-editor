#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"
#include <SDL.h>
#include "effects.h"
#include <vector>
#include <string>
extern "C" { const char* tinyfd_openFileDialog(const char*,const char*); }

struct Clip{ std::string file; float pos=0,dur=5; };
struct Project{ std::vector<Clip> clips; };

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* w=SDL_CreateWindow("CoConut Editor",0,0,1600,900,SDL_WINDOW_OPENGL);
    SDL_Renderer* r=SDL_CreateRenderer(w,-1,0);
    auto gl=SDL_GL_CreateContext(w);
    IMGUI_CHECKVERSION(); ImGui::CreateContext(); ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(w,gl); ImGui_ImplOpenGL2_Init();

    Project p; auto fx=getEffects(); int tab=0; bool run=true;
    while(run){
        SDL_Event e; while(SDL_PollEvent(&e)){ ImGui_ImplSDL2_ProcessEvent(&e); if(e.type==SDL_QUIT) run=false; }
        ImGui_ImplOpenGL2_NewFrame(); ImGui_ImplSDL2_NewFrame(); ImGui::NewFrame();
        
        ImGui::SetNextWindowPos({0,0}); ImGui::SetNextWindowSize({1600,900});
        ImGui::Begin("CoConut",0,ImGuiWindowFlags_NoDecoration);
        
        if(ImGui::Button("Timeline")) tab=0; ImGui::SameLine();
        if(ImGui::Button("Efeitos (500)")) tab=1; ImGui::SameLine();
        if(ImGui::Button("Textos")) tab=2; ImGui::SameLine();
        if(ImGui::Button("Cor")) tab=3; ImGui::SameLine();
        if(ImGui::Button("Export")) tab=4;
        
        ImGui::Separator();
        if(tab==0){
            if(ImGui::Button("Importar")){ auto f=tinyfd_openFileDialog("Video",""); if(f){ p.clips.push_back({f}); } }
            for(auto& c:p.clips) ImGui::Text("%s", c.file.c_str());
        }
        if(tab==1){ for(auto& e:fx) if(ImGui::Button(e.name.c_str())){} }
        if(tab==4){ if(ImGui::Button("Exportar MP4")){} }
        
        ImGui::End();
        ImGui::Render(); glClear(GL_COLOR_BUFFER_BIT); ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData()); SDL_GL_SwapWindow(w);
    }
    return 0;
}
