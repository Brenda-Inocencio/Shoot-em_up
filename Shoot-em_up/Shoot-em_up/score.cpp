#include "score.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Score::Score(SDL_Renderer* renderer) {
	score = 0;
    SDL_Color textColor = {255, 255, 255, 255};
    TTF_Font* font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    textSurface = TTF_RenderText_Solid(font, "Menu", 4, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    if (!textTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void Score::UpdateScore() {
    score += 100;
}

void Score::Render(SDL_Renderer* renderer) {
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {495, 805, (float)tw, (float)th};
        SDL_RenderTexture(renderer, textTexture, nullptr, &textRect);
        
    }
}