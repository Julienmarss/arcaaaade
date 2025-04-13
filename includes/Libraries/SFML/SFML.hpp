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
         * @brief Destructor that cleans up SFML ressources.
         */
        ~SFML() override;

        void Initialize() override;
        void Open() override;
        void Close() override;
        bool IsOpen() override;
        void Display() override;
        void Clear() override;

        void DrawComponent(std::shared_ptr<arc::RenderComponent>) override;
        void DrawComponents(std::vector<std::shared_ptr<arc::RenderComponent>> components) override;
        void DrawMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map) override;
        void DrawMenu(std::shared_ptr<arc::MenuComponent> menu) override;
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
         * @brief Internally updates the menu render state.
         * 
         * @param menu The menu to display.
         */
        void changeMenu(std::shared_ptr<arc::MenuComponent> menu);

        /**
         * @brief Internally updates the map render state.
         * 
         * @param map The game map to render.
         */
        void changeMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map);

        /**
         * @brief Maps arcade colors to SFML colors.
         * 
         * @param color The arcade color to map.
         * @return The corresponding SFML color.
         */
        sf::Color mapColor(arc::Colors color) const;

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
