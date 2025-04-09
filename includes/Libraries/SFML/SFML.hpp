/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** SFML.hpp
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
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
     * @class SFML
     * @brief Implementation of AGraphicLibrary using the SFML library.
     * 
     * Provides window-based graphical rendering with support for images, text, input handling, and audio.
     */
    class SFML : public AGraphicLibrary {
    public:
        /**
         * @brief Constructs the SFML graphical backend.
         */
        SFML();

        /**
         * @brief Destructor that cleans up SFML resources.
         */
        ~SFML() override;

        void Initialize() override;
        void Open() override;
        void Close() override;
        bool IsOpen() override;
        void Display() override;
        void Clear() override;

        void DrawComponent(const arc::RenderComponent& component) override;
        void DrawComponents(const std::vector<arc::RenderComponent>& components) override;
        void DrawMap(const std::vector<std::vector<arc::RenderComponent>>& map) override;
        void DrawMenu(const arc::MenuComponent& menu) override;
        void DrawText(const arc::TextComponent& text) override;
        void DrawScore(const int& score, const arc::TextComponent& text) override;

        std::pair<int, int> GetMousePos() const override;
        arc::click GetMouseState() const override;
        arc::Event HandleEvent() override;
        char GetKeyPressed() override;
        std::string GetName() const override;

        void LoadResources(std::string filepath, arc::type type) override;
        void UnloadResources(std::string filepath, arc::type type) override;
        void LaunchMusic(std::string filepath) override;
        void StopMusic(std::string filepath) override;

    private:
        /**
         * @brief Internally updates the menu render state.
         * 
         * @param menu The menu to display.
         */
        void changeMenu(const arc::MenuComponent& menu);

        /**
         * @brief Internally updates the map render state.
         * 
         * @param map The game map to render.
         */
        void changeMap(const std::vector<std::vector<arc::RenderComponent>>& map);

        sf::RenderWindow _window; ///< SFML window object
        sf::Event _event; ///< Event handler for SFML
        sf::Keyboard::Key _keyPressed; ///< Stores the last key pressed
        std::string _name = "SFML"; ///< Name of the library

        std::map<std::string, std::unique_ptr<sf::Texture>> _textures; ///< Loaded textures
        std::map<std::string, std::unique_ptr<sf::Sprite>> _sprites;   ///< Associated sprites
        std::map<std::string, std::unique_ptr<sf::Font>> _fonts;       ///< Loaded fonts
        std::map<std::string, std::unique_ptr<sf::Text>> _texts;       ///< Displayable texts
        std::vector<sf::RectangleShape> _rectangles;                   ///< Drawable rectangles
        std::unique_ptr<sf::Text> _scoretext;                          ///< Rendered score text
    };

}

#endif // SFML_HPP_
