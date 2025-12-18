#include "score.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

Score::Score(SDL_Renderer* renderer) {
    score = 0;
    SDL_Color textColor = { 255, 255, 255, 255 };
    font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    textSurface = TTF_RenderText_Solid(font, "Score", 6, textColor);
    scoreSurface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), 6, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_DestroySurface(textSurface);
    if (!textTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void Score::UpdateScore(SDL_Renderer* renderer) {
    score += 100;
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    SDL_Color text_color = { 255, 255, 255, 255 };
    scoreSurface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), 6, text_color);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_DestroySurface(scoreSurface);
}

void Score::Render(SDL_Renderer* renderer) {
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = { 495, 100, (float)tw, (float)th };
        SDL_RenderTexture(renderer, textTexture, nullptr, &textRect);
    }
    if (scoreTexture) {
        float tw, th;
        SDL_GetTextureSize(scoreTexture, &tw, &th);
        SDL_FRect textRect = { 495, 200, (float)tw, (float)th };
        SDL_RenderTexture(renderer, scoreTexture, nullptr, &textRect);
    }
}