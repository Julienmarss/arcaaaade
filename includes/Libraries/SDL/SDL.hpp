/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** SDL.hpp
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Core/Abstract/AGraphicLibrary.hpp"
#include "Interface/IGraphicLibrary.hpp"
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include "Core/Click.hpp"
#include <vector>
#include <map>
#include <any>
#include <memory>
#include <string>

namespace arc::display {

    /**
     * @class SDL
     * @brief Implementation of AGraphicLibrary using the SDL2 library.
     * 
     * Provides window-based graphical rendering with support for images, text, and input handling.
     */
    class SDL : public AGraphicLibrary {
    public:
        /**
         * @brief Constructs the SDL graphical backend.
         */
        SDL();

        /**
         * @brief Destructor that cleans up SDL ressources.
         */
        ~SDL() override;

        void Initialize() override;
        void Open() override;
        void Close() override;
        bool IsOpen() override;
        void Display() override;
        void Clear() override;

        void DrawComponent(std::shared_ptr<arc::RenderComponent>) override;
        void DrawComponents(std::vector<std::shared_ptr<arc::RenderComponent>> components) override;
        void DrawMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map) override;
        void DrawMenu(std::shared_ptr<arc::MenuComponent> menu ) override;
        void DrawText(std::shared_ptr<arc::TextComponent> text) override;
        void DrawScore(const int& score, std::shared_ptr<arc::TextComponent>text) override;

        std::pair<int, int> GetMousePos() const override;
        arc::click GetMouseState() const override;
        Event HandleEvent() override;
        char GetKeyPressed() override;
        std::string GetName() const override;

        void LoadResources(std::string filepath, type type) override;
        void UnloadResources(std::string filepath, type type) override;
        void LaunchMusic(std::string filepath) override;
        void StopMusic(std::string filepath) override;

    private:
        /**
         * @brief Maps a color enum to SDL_Color
         * @param color The color enum to map
         * @return SDL_Color representation
         */
        SDL_Color mapColor(arc::Colors color) const;
        SDL_Window* _window;                                  ///< SDL window handle
        SDL_Renderer* _renderer;                              ///< SDL renderer 
        bool _isOpen;                                         ///< Window open state
        SDL_Event _event;                                     ///< Current SDL event
        char _keyPressed;                                     ///< Last key pressed
        std::string _name = "SDL";                            ///< Library name

        std::map<std::string, SDL_Texture*> _textures;        ///< Loaded textures
        std::map<std::string, TTF_Font*> _fonts;              ///< Loaded fonts
        std::vector<SDL_Rect> _mapRects;                      ///< Rectangles for map rendering
        std::vector<SDL_Color> _mapColors;                    ///< Colors for map rendering
        SDL_Color _textColor;                                 ///< Current text color
    };

}

/**
 * @brief Entry point for dynamic loading
 * @return Pointer to new SDL instance
 */
extern "C" void *entryPoint();

#endif // SDL_HPP_