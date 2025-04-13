#ifndef SDLWRAPPER_HPP
# define SDLWRAPPER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>

namespace arc::display {
    class SDLWrapper
    {
    public:
        static void init();
        static SDL_Window* createWindow(const char* title, int w, int h) ;
        static SDL_Renderer* createRenderer(SDL_Window* window);
        static TTF_Font* loadFont(const std::string& path, int size);
        static SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, 
                                            const std::string& text, SDL_Color color);
        static void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, 
                                int x, int y, int w, int h);
        static void setDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        static void clearRenderer(SDL_Renderer* renderer);
        static void presentRenderer(SDL_Renderer* renderer);
        static void fillRect(SDL_Renderer* renderer, const SDL_Rect& rect);
        static void cleanup(SDL_Window* window, SDL_Renderer* renderer);
        static bool pollEvent(SDL_Event& event);
        static void destroyTexture(SDL_Texture* texture);
        static void destroyFont(TTF_Font* font);
        static void drawText(SDL_Renderer* renderer, TTF_Font* font,
            const std::string& text, SDL_Color color,
            int x, int y);
        static void drawScore(SDL_Renderer* renderer, TTF_Font* font,
                    int score, const std::string& text,
                    SDL_Color color, int x, int y);

        static SDL_Color createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
        static void drawMenu(SDL_Renderer* renderer, TTF_Font* font,
            const std::string& title,
            const std::vector<std::string>& items,
            const std::string& selectedItem,
            int startX, int startY,
            SDL_Color titleColor,
            SDL_Color normalColor,
            SDL_Color selectedColor);
        };
}

#endif