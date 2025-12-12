#pragma once
#include "button.h"

class Play : public Button {
public:

    Play(SDL_Renderer* renderer);
    ~Play();
    void Render(SDL_Renderer* _renderer) override;
    void Press(SDL_Renderer* _renderer) override;
};