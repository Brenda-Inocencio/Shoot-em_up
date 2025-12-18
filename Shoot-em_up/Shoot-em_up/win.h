#pragma once
#include "button.h"


class Win : public Button {
    SDL_Surface* winSurface;
    SDL_Texture* winTexture;
public:
    Win(SDL_Renderer* _renderer);
    ~Win();
    void Render(SDL_Renderer* renderer) override;
    void Press(SDL_Renderer* renderer) override;
};