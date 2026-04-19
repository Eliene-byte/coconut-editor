#pragma once
#include <vector>
#include <string>
struct EffectPreset { std::string name, category; float bright, contrast, sat, fadeIn, fadeOut, speed; };
inline std::vector<EffectPreset> getEffects(){
    return {
        {"Teal & Orange", "Cinematic", -5,1.4f,1.2f,0,0,1},
        {"Noir", "Cinematic", 0,1.8f,0,1,1,1},
        {"Vintage 70s", "Cinematic", 5,1.1f,0.7f,0.3f,0.3f,1},
        {"Gamer Neon", "Gaming", 10,1.3f,1.5f,0,0,1},
        {"Vlog Clean", "Vlog", 5,1.1f,1.1f,0.2f,0.2f,1},
    };
}
