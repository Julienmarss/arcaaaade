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
#include "Core/Components/IObject.hpp"
#include <vector>
#include <map>
#include <any>

namespace arc::display {
    class SFML : public AGraphicLibrary {
        public:
            SFML();
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
            void DrawScore(const int& score) override;
            
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
            sf::RenderWindow _window;
            sf::Event _event;
            sf::Keyboard::Key _keyPressed;
            std::string _name = "SFML";
            std::map<std::string, sf::Texture> _textures;
            std::map<std::string, sf::Sprite> _sprites;
            std::map<std::string, sf::Font> _fonts;
            std::map<std::string, sf::Text> _texts;
    };
}

#endif