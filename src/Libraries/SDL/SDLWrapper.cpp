/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** SDLWrapper.cpp
*/

#include "Libraries/SDL/SDLWrapper.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_ttf.h>

void arc::display::SDLWrapper::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }
    if (TTF_Init() < 0) {
        throw std::runtime_error("TTF could not initialize! TTF_Error: " + std::string(TTF_GetError()));
    }
}



SDL_Window* arc::display::SDLWrapper::createWindow(const char* title, int width, int height)
{
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
    return window;
}

SDL_Renderer* arc::display::SDLWrapper::createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
    return renderer;
}

TTF_Font* arc::display::SDLWrapper::loadFont(const std::string& path, int size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        throw std::runtime_error("Font could not be loaded! TTF_Error: " + std::string(TTF_GetError()));
    }
    return font;
}

SDL_Texture* arc::display::SDLWrapper::createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Text surface could not be created! TTF_Error: " + std::string(TTF_GetError()));
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        throw std::runtime_error("Texture could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
    return texture;
}
void arc::display::SDLWrapper::destroyTexture(SDL_Texture* texture)
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
void arc::display::SDLWrapper::destroyFont(TTF_Font* font)
{
    if (font) {
        TTF_CloseFont(font);
    }
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}
void arc::display::SDLWrapper::setDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if (SDL_SetRenderDrawColor(renderer, r, g, b, a) < 0) {
        throw std::runtime_error("Set draw color failed: " + std::string(SDL_GetError()));
    }
}

void arc::display::SDLWrapper::clearRenderer(SDL_Renderer* renderer)
{
    if (SDL_RenderClear(renderer) < 0) {
        throw std::runtime_error("Render clear failed: " + std::string(SDL_GetError()));
    }
}

void arc::display::SDLWrapper::presentRenderer(SDL_Renderer* renderer)
{
    SDL_RenderPresent(renderer);
}

void arc::display::SDLWrapper::fillRect(SDL_Renderer* renderer, const SDL_Rect& rect)
{
    if (SDL_RenderFillRect(renderer, &rect) < 0) {
        throw std::runtime_error("Fill rect failed: " + std::string(SDL_GetError()));
    }
}

void arc::display::SDLWrapper::cleanup(SDL_Window* window, SDL_Renderer* renderer)
{
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

bool arc::display::SDLWrapper::pollEvent(SDL_Event& event)
{
    return SDL_PollEvent(&event) == 1;
}

void arc::display::SDLWrapper::drawText(SDL_Renderer* renderer, TTF_Font* font,
    const std::string& text, SDL_Color color,
    int x, int y)
{
    if (!font || !renderer) {
        throw std::runtime_error("Invalid font or renderer");
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Failed to render text: " + std::string(TTF_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
    SDL_FreeSurface(surface);
        throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void arc::display::SDLWrapper::drawScore(SDL_Renderer* renderer, TTF_Font* font,
     int score, const std::string& text,
     SDL_Color color, int x, int y)
{
    std::string scoreText = text + ": " + std::to_string(score);
    drawText(renderer, font, scoreText, color, x, y);
}

SDL_Color arc::display::SDLWrapper::createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return {r, g, b, a};
}
void arc::display::SDLWrapper::drawMenu(SDL_Renderer* renderer, TTF_Font* font,
    const std::string& title,
    const std::vector<std::string>& items,
    const std::string& selectedItem,
    int startX, int startY,
    SDL_Color titleColor,
    SDL_Color normalColor,
    SDL_Color selectedColor)
{
    if (!font || !renderer) {
        throw std::runtime_error("Invalid font or renderer");
    }

    try {
        drawText(renderer, font, title, titleColor, startX, startY);
        int itemY = startY + 50;
        const int ITEM_SPACING = 30; 
        for (const auto& item : items) {
            SDL_Color currentColor = (item == selectedItem) ? selectedColor : normalColor;
            std::string displayText = (item == selectedItem) ? "> " + item : "  " + item;
            drawText(renderer, font, displayText, currentColor, startX, itemY);
            itemY += ITEM_SPACING;
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Menu drawing failed: " + std::string(e.what()));
    }
}