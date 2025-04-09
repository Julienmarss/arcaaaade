/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** IGraphicLibrary.hpp
*/

#ifndef IGRAPHICLIBRARY
# define IGRAPHICLIBRARY

#include <iostream>
#include <string>
#include <vector>
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include "Core/Click.hpp"
#include "Core/Type.hpp"

namespace arc {

    /**
     * @class IGraphicLibrary
     * @brief Interface for all graphical libraries in the arcade system.
     * 
     * Each graphic library (e.g., SFML, SDL, ncurses) must implement this interface
     * to handle rendering, input, and resource management.
     */
    class IGraphicLibrary {
    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~IGraphicLibrary() = default;

        /**
         * @brief Initializes the graphic library (window creation, context setup).
         */
        virtual void Initialize() = 0;

        /**
         * @brief Opens the graphic interface (typically starts a render window).
         */
        virtual void Open() = 0;

        /**
         * @brief Closes the graphic interface and releases associated resources.
         */
        virtual void Close() = 0;

        /**
         * @brief Checks whether the window or interface is currently open.
         * 
         * @return True if open, false otherwise.
         */
        virtual bool IsOpen() = 0;

        /**
         * @brief Displays the current render buffer to the screen.
         */
        virtual void Display() = 0;

        /**
         * @brief Clears the current render buffer.
         */
        virtual void Clear() = 0;

        /**
         * @brief Draws a single renderable component.
         * 
         * @param component The RenderComponent to draw.
         */
        virtual void DrawComponent(const RenderComponent& component) = 0;

        /**
         * @brief Draws a list of renderable components.
         * 
         * @param components A vector of RenderComponents.
         */
        virtual void DrawComponents(const std::vector<RenderComponent>& components) = 0;

        /**
         * @brief Draws a 2D map made of renderable components.
         * 
         * @param map A 2D vector of RenderComponents.
         */
        virtual void DrawMap(const std::vector<std::vector<RenderComponent>>& map) = 0;

        /**
         * @brief Draws a menu component on screen.
         * 
         * @param menu The MenuComponent to render.
         */
        virtual void DrawMenu(const MenuComponent& menu) = 0;

        /**
         * @brief Draws a text component on screen.
         * 
         * @param text The TextComponent to render.
         */
        virtual void DrawText(const TextComponent& text) = 0;

        /**
         * @brief Draws the score using a text template.
         * 
         * @param score The numeric score.
         * @param text The TextComponent for formatting or styling.
         */
        virtual void DrawScore(const int& score, const TextComponent& text) = 0;

        /**
         * @brief Gets the current mouse position.
         * 
         * @return A pair representing (x, y) coordinates.
         */
        virtual std::pair<int, int> GetMousePos() const = 0;

        /**
         * @brief Gets the current state of the mouse (e.g., clicked, released).
         * 
         * @return The current click state.
         */
        virtual click GetMouseState() const = 0;

        /**
         * @brief Handles and returns the next user input event.
         * 
         * @return The processed event.
         */
        virtual Event HandleEvent() = 0;

        /**
         * @brief Gets the last key pressed by the user.
         * 
         * @return The character of the key pressed.
         */
        virtual char GetKeyPressed() = 0;

        /**
         * @brief Loads a graphical or audio resource from a file.
         * 
         * @param filepath The path to the resource file.
         * @param type The type of resource (texture, font, sound, etc.).
         */
        virtual void LoadResources(std::string filepath, type type) = 0;

        /**
         * @brief Unloads a previously loaded resource.
         * 
         * @param filepath The path to the resource file.
         * @param type The type of resource.
         */
        virtual void UnloadResources(std::string filepath, type type) = 0;

        /**
         * @brief Launches background music or sound.
         * 
         * @param filepath Path to the music file.
         */
        virtual void LaunchMusic(std::string filepath) = 0;

        /**
         * @brief Stops the currently playing music.
         * 
         * @param filepath Path to the music file.
         */
        virtual void StopMusic(std::string filepath) = 0;

        /**
         * @brief Gets the name of the graphic library.
         * 
         * @return The library name as a string.
         */
        virtual std::string GetName() const = 0;
    };

} // namespace arc

#endif // IGRAPHICLIBRARY
