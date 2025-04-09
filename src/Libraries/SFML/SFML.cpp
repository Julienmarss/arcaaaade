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
    this->_scoretext = std::make_unique<sf::Text>();

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
{    this->_window.display();
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
    this->_window.draw(*_sprites["resources/background.png"]);
    this->changeMap(map);
    for (const auto &pair : _rectangles) {
        this->_window.draw(pair);
    }
    (void)map;
}


void arc::display::SFML::DrawMenu(const arc::MenuComponent& menu)
{
    this->changeMenu(menu);
    this->_window.draw(*_sprites["resources/background.png"]);
    for (auto &item : _texts) {
        this->_window.draw(*item.second);
    }
}

void arc::display::SFML::DrawText(const arc::TextComponent& text)
{
    (void)text;
}

void arc::display::SFML::DrawScore(const int& score, const arc::TextComponent &text)
{
    this->_scoretext->setString(std::to_string(score));
    this->_scoretext->setCharacterSize(text.GetCharacterSize());
    this->_scoretext->setFont(*_fonts[text.GetFont()]);
    this->_scoretext->setFillColor(sf::Color::White);
    this->_scoretext->setPosition(10, 10);
    this->_window.draw(*_scoretext);
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
    this->_keyPressed = sf::Keyboard::Unknown;
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed) {
            this->_window.close();
        }
        if (this->_event.type == sf::Event::KeyPressed) {
            if (this->_event.key.code == sf::Keyboard::Escape) {
                return arc::Event::ESCAPE;
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
            if (this->_event.key.code == sf::Keyboard::Enter) {
                return arc::Event::ENTER;
            }
            if (this->_event.key.code == sf::Keyboard::BackSpace) {
                return arc::Event::BACKSPACE;
            }
            if (this->_event.key.code == sf::Keyboard::Delete) {
                return arc::Event::DELETE;
            }
            const sf::Keyboard::Key keycode = this->_event.key.code;
            if (keycode >= sf::Keyboard::A && keycode <= sf::Keyboard::Z) {
                this->_keyPressed = keycode;
            }
            return arc::Event::TEXT_INPUT;
        }
    }
    return arc::Event::TEXT_INPUT;
}

char arc::display::SFML::GetKeyPressed()
{
    if (this->_keyPressed == sf::Keyboard::Unknown)
        return 0;
    return this->_keyPressed + 97;
}

std::string arc::display::SFML::GetName() const
{
    return _name;
}

void arc::display::SFML::LoadResources(std::string filepath, arc::type type)
{
    if (type == arc::type::TEXTURE) {
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(filepath)) {
            throw std::runtime_error("Failed to load texture");
        }

        auto sprite = std::make_unique<sf::Sprite>(*texture);
        _textures[filepath] = std::move(texture);
        _sprites[filepath] = std::move(sprite);
    } else if (type == arc::type::FONT) {
        auto font = std::make_unique<sf::Font>();
        if (!font->loadFromFile(filepath)) {
            throw std::runtime_error("Failed to load font");
        }
        _fonts[filepath] = std::move(font);
    } else if (type == arc::type::TEXT) {
        auto text = std::make_unique<sf::Text>();
        _texts[filepath] = std::move(text);
        _texts[filepath]->setFont(*_fonts["resources/font.ttf"]);
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


void arc::display::SFML::changeMenu(const arc::MenuComponent& menu)
{
    _texts.clear();

    int y = (_window.getSize().y / 2) - (menu.GetItems().size() * 30) / 2;
    int x = (_window.getSize().x / 2) - (menu.GetTitle().GetText().size() * 10) / 2;

    this->LoadResources(menu.GetTitle().GetText(), arc::type::TEXT);
    if (auto it = _texts.find(menu.GetTitle().GetText()); it != _texts.end()) {
        it->second->setString(menu.GetTitle().GetText());
        it->second->setCharacterSize(menu.GetTitle().GetCharacterSize());
        it->second->setFont(*_fonts[menu.GetTitle().GetFont()]);
        it->second->setFillColor(sf::Color::Red);
        it->second->setPosition(x, y);
    }
    y += 50;

    for (const auto& item : menu.GetItems()) {
        this->LoadResources(item.GetText(), arc::type::TEXT);
        if (auto it = _texts.find(item.GetText()); it != _texts.end()) {
            it->second->setString(item.GetText());
            it->second->setCharacterSize(item.GetCharacterSize());
            it->second->setFont(*_fonts[item.GetFont()]);
            it->second->setPosition(x, y);
            it->second->setFillColor(item.GetText() == menu.GetSelectedItem().GetText() ? 
                                   sf::Color::Green : sf::Color::White);
            y += 30;
        }
    }
}

void arc::display::SFML::changeMap(const std::vector<std::vector<arc::RenderComponent>>& map)
{
    int middle = (this->_window.getSize().x / 2) - (map[0].size() * 10) / 2;
    this->_rectangles.clear();
    for (const auto& row : map) {
        for (const auto& component : row) {
            sf::RectangleShape rectangle(sf::Vector2f(10, 10));
            rectangle.setPosition(((component.GetY() * 10) + middle), (component.GetX() * 10) + middle);
            if (component.GetType() == arc::TypeComponent::WALL) {
                rectangle.setFillColor(sf::Color::Red);
            } else if (component.GetType() == arc::TypeComponent::PLAYER) {
                rectangle.setFillColor(sf::Color::Green);
            } else if (component.GetType() == arc::TypeComponent::ENEMY) {
                rectangle.setFillColor(sf::Color::Blue);
            } else if (component.GetType() == arc::TypeComponent::COLLECTIBLE) {
                rectangle.setFillColor(sf::Color::Yellow);
            } else {
                rectangle.setFillColor(sf::Color::White);
            }
            _rectangles.push_back(rectangle);
        }
    }
}