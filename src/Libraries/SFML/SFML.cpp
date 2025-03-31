/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** SFML.cpp
*/

#include "Libraries/SFML/SFML.hpp"
#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGraphicLibrary.hpp"
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include <ncurses.h>


extern "C" void *entryPoint() {
    return new arc::display::SFML();
}

arc::display::SFML::SFML()
{
}

arc::display::SFML::~SFML()
{
}

void arc::display::SFML::Initialize()
{
    this->LoadResources("resources/background.png", arc::type::TEXTURE);
    this->LoadResources("resources/font.ttf", arc::type::FONT);
}

void arc::display::SFML::Open()
{
    _window.create(sf::VideoMode(800, 600), "Arcade");
    _event = sf::Event();
}

void arc::display::SFML::Close()
{
}

bool arc::display::SFML::IsOpen()
{
    return this->_window.isOpen();
}

void arc::display::SFML::Display()
{
    this->_window.display();
}

void arc::display::SFML::Clear()
{
    this->_window.clear(sf::Color::Black);
}

void arc::display::SFML::DrawComponent(const arc::RenderComponent& component)
{
    (void)component;
}

void arc::display::SFML::DrawComponents(const std::vector<arc::RenderComponent>& components)
{
    (void)components;
}

void arc::display::SFML::DrawMap(const std::vector<std::vector<arc::RenderComponent>>& map)
{
    (void)map;
}

void arc::display::SFML::DrawMenu(const arc::MenuComponent& map)
{
//     sf::Text text;
//     text.setFont(_fonts["resources/font.ttf"]);
//     text.setString(map.GetTitle());
//     text.setCharacterSize(24);
//     text.setFillColor(sf::Color::White);
//     for (const auto& item : map.GetItems()) {
//         sf::Text text;
//         text.setFont(_fonts["resources/font.ttf"]);
//         text.setString(item);
//         text.setCharacterSize(16);
//         text.setFillColor(sf::Color::White);
//         text.setPosition(100, 100 + 50 * (&item - &map.GetItems()[0])); 
//         if (item == map.GetSelectedItem()) {
//             text.setFillColor(sf::Color::Red);
//         }
//         this->_window.draw(text);
//     }
    this->_window.draw(this->_sprites["resources/background.png"]);
    (void) map;
}

void arc::display::SFML::DrawText(const arc::TextComponent& text)
{
    (void)text;
}

void arc::display::SFML::DrawScore(const int& score)
{
    (void)score;
}

std::pair<int, int> arc::display::SFML::GetMousePos() const
{
    return std::pair<int, int>();
}

arc::click arc::display::SFML::GetMouseState() const
{
    return arc::click::NOTHING;
}

arc::Event arc::display::SFML::HandleEvent()
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed) {
            this->_window.close();
        }
        if (this->_event.type == sf::Event::KeyPressed) {
            if (this->_event.key.code == sf::Keyboard::Escape) {
                this->_window.close();
            }
            if (this->_event.key.code == sf::Keyboard::Up) {
                return arc::Event::UP;
            }
            if (this->_event.key.code == sf::Keyboard::Down) {
                return arc::Event::DOWN;
            }
            if (this->_event.key.code == sf::Keyboard::Left) {
                return arc::Event::LEFT;
            }
            if (this->_event.key.code == sf::Keyboard::Right) {
                return arc::Event::RIGHT;
            }
            this->_keyPressed = this->_event.key.code;
            return arc::Event::TEXT_INPUT;
        }
    }
    return arc::Event::TEXT_INPUT;
}

char arc::display::SFML::GetKeyPressed()
{
    return 0;
}

std::string arc::display::SFML::GetName() const
{
    return _name;
}

void arc::display::SFML::LoadResources(std::string filepath, arc::type type)
{
    if (type == arc::type::TEXTURE) {
        sf::Texture texture;
        if (!texture.loadFromFile(filepath)) {
            throw std::runtime_error("Failed to load texture");
        }

        sf::Sprite sprite(texture);
        _textures[filepath] = texture;
        _sprites[filepath] = sprite;
    } else if (type == arc::type::FONT) {
        sf::Font font;
        if (!font.loadFromFile(filepath)) {
            throw std::runtime_error("Failed to load font");
        }
        _fonts[filepath] = font;
    } else if (type == arc::type::TEXT) {
        sf::Text text;
        _texts[filepath] = text;
    }
}

void arc::display::SFML::UnloadResources(std::string filepath, arc::type type)
{
    if (type == arc::type::TEXTURE) {
        _textures.erase(filepath);
        _sprites.erase(filepath);
    } else if (type == arc::type::FONT) {
        _fonts.erase(filepath);
    } else if (type == arc::type::TEXT) {
        _texts.erase(filepath);
    }
}

void arc::display::SFML::LaunchMusic(std::string filepath)
{
    (void)filepath;
}

void arc::display::SFML::StopMusic(std::string filepath)
{
    (void)filepath;
}