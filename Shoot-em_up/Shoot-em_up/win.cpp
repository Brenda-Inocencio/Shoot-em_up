#include "win.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Win::Win(SDL_Renderer* renderer) {
    TTF_Font* winFont = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 28);
    SDL_Color textColor = {255, 255, 255, 255};
    if (!winFont) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    winSurface = TTF_RenderText_Solid(winFont, "You lose", 9, textColor);
    winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
    SDL_DestroySurface(winSurface);
    if (!winTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }

    font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    textSurface = TTF_RenderText_Solid(font, "Exit", 4, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    if (!textTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void Win::Render(SDL_Renderer* _renderer) {
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 150, 0, 0, 200);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (winTexture) {
        float tw, th;
        SDL_GetTextureSize(winTexture, &tw, &th);
        SDL_FRect textRect = {475, 300, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, winTexture, nullptr, &textRect);
    }
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 20, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

void Win::Press(SDL_Renderer* _renderer) {
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 100, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 20, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

Win::~Win() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}