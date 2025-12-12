#include "pause.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Pause::Pause(SDL_Renderer* renderer) {
    font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }

    SDL_Color textColor = {255, 255, 255, 255};
    pauseSurface = TTF_RenderText_Solid(font, "Pause", 5, textColor);
    pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
    SDL_DestroySurface(pauseSurface);
    if (!pauseTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
    textSurface = TTF_RenderText_Solid(font, "Menu", 4, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    if (!textTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void Pause::Render(SDL_Renderer* _renderer) {
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 150, 0, 0, 200);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (pauseTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {200, 100, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 30, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

void Pause::Press(SDL_Renderer* _renderer) {
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 100, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 25, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

Pause::~Pause() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}