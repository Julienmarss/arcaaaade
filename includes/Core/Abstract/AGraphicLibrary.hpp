/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** AGameLibrary.hpp
*/

#ifndef AGAMELIBRARY_HPP
# define AGAMELIBRARY_HPP

#include "Interface/IGraphicLibrary.hpp"
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include "Core/Click.hpp"
#include <map>
#include <any>

namespace arc::display {

    /**
     * @class AGraphicLibrary
     * @brief Abstract base class for all graphical libraries.
     * 
     * This class provides a virtual interface and common protected data members 
     * to help implement graphical rendering using libraries like SFML, SDL, etc.
     * 
     * It inherits from IGraphicLibrary and extends it with shared data like asset management.
     */
    class AGraphicLibrary : virtual public IGraphicLibrary {
    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~AGraphicLibrary() = default;

        /**
         * @brief Initializes the graphic library (window, context, resources).
         */
        virtual void Initialize() = 0;

        /**
         * @brief Opens the display window or interface.
         */
        virtual void Open() = 0;

        /**
         * @brief Closes the display window and frees resources.
         */
        virtual void Close() = 0;

        /**
         * @brief Checks whether the window is currently open.
         * 
         * @return True if the window is open, false otherwise.
         */
        virtual bool IsOpen() = 0;

        /**
         * @brief Displays the rendered content to the screen.
         */
        virtual void Display() = 0;

        /**
         * @brief Clears the current rendering buffer.
         */
        virtual void Clear() = 0;

        /**
         * @brief Draws a single RenderComponent to the screen.
         * 
         * @param component The renderable object.
         */
        virtual void DrawComponent(const arc::RenderComponent& component) = 0;

        /**
         * @brief Draws multiple RenderComponents at once.
         * 
         * @param components A vector of RenderComponents.
         */
        virtual void DrawComponents(const std::vector<arc::RenderComponent>& components) = 0;

        /**
         * @brief Draws a 2D map composed of RenderComponents.
         * 
         * @param map A 2D vector of RenderComponents.
         */
        virtual void DrawMap(const std::vector<std::vector<arc::RenderComponent>>& map) = 0;

        /**
         * @brief Draws a menu to the screen.
         * 
         * @param map The MenuComponent to render.
         */
        virtual void DrawMenu(const arc::MenuComponent& map) = 0;

        /**
         * @brief Draws a text component.
         * 
         * @param text The TextComponent to render.
         */
        virtual void DrawText(const arc::TextComponent& text) = 0;

        /**
         * @brief Draws a score using a text template.
         * 
         * @param score The current score.
         * @param text The text component template.
         */
        virtual void DrawScore(const int& score, const arc::TextComponent &text) = 0;

        /**
         * @brief Returns the current position of the mouse.
         * 
         * @return A pair representing (x, y) coordinates.
         */
        virtual std::pair<int, int> GetMousePos() const = 0;

        /**
         * @brief Returns the current mouse click state.
         * 
         * @return The current click status.
         */
        virtual click GetMouseState() const = 0;

        /**
         * @brief Handles and returns the next input event.
         * 
         * @return The triggered Event.
         */
        virtual Event HandleEvent() = 0;

        /**
         * @brief Returns the last key pressed by the user.
         * 
         * @return A char representing the key.
         */
        virtual char GetKeyPressed() = 0;

        /**
         * @brief Loads a resource (e.g., image, font, sound).
         * 
         * @param filepath Path to the file.
         * @param type Type of resource to load.
         */
        virtual void LoadResources(std::string filepath, arc::type type) = 0;

        /**
         * @brief Unloads a previously loaded resource.
         * 
         * @param filepath Path to the file.
         * @param type Type of resource to unload.
         */
        virtual void UnloadResources(std::string filepath, arc::type type) = 0;

        /**
         * @brief Starts playing music from a file.
         * 
         * @param filepath Path to the music file.
         */
        virtual void LaunchMusic(std::string filepath) = 0;

        /**
         * @brief Stops playing the specified music.
         * 
         * @param filepath Path to the music file.
         */
        virtual void StopMusic(std::string filepath) = 0;

        /**
         * @brief Gets the name of the current graphic library.
         * 
         * @return The name as a string.
         */
        virtual std::string GetName() const = 0;

    protected:
        std::string _name;                           ///< Name of the graphic library.
        std::map<std::string, std::any> _assets;     ///< Generic asset storage (textures, fonts, etc.).
    };

} // namespace arc::display

#endif // AGAMELIBRARY_HPP
