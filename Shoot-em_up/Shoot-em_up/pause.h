#pragma once
#include "button.h"


class Pause : public Button {
    SDL_Surface* pauseSurface;
    SDL_Texture* pauseTexture;
public:
    Pause(SDL_Renderer* _renderer);
    ~Pause();
    void Render(SDL_Renderer* renderer) override;
    void Press(SDL_Renderer* renderer) override;
};