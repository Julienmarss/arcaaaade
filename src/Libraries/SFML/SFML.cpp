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
    this->_scoretext = std::make_unique<sf::Text>();
    std::cout << "SFML Initialize" << std::endl;

}

void arc::display::SFML::Open()
{
    _window.create(sf::VideoMode(800, 600), "Arcade - SFML");
    _event = sf::Event();
    std::cout << "SFML Open" << std::endl;
    _window.setFramerateLimit(60);
}

void arc::display::SFML::Close()
{
    _window.close();
    _textures.clear();
    _sprites.clear();
    _fonts.clear();
    _texts.clear();
    _rectangles.clear();
    _scoretext.reset();
    _window.clear();
    std::cout << "SFML Close" << std::endl;
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

void arc::display::SFML::DrawComponent(std::shared_ptr<arc::RenderComponent> component)
{
    (void)component;
}

void arc::display::SFML::DrawComponents(std::vector<std::shared_ptr<arc::RenderComponent>> components)
{
    (void)components;
}

void arc::display::SFML::DrawMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map)
{
    this->changeMap(map);
    for (const auto &pair : _rectangles) {
        this->_window.draw(pair);
    }
    (void)map;
}


void arc::display::SFML::DrawMenu(std::shared_ptr<arc::MenuComponent> menu)
{
    this->changeMenu(menu);
    for (auto &item : _texts) {
        this->_window.draw(*item.second);
    }
}

void arc::display::SFML::DrawText(std::shared_ptr<arc::TextComponent> text)
{
    _texts.clear();
    this->LoadResources(text->GetText(), type::TEXT);
    if (text->GetFont() != "" && _fonts.find(text->GetFont()) == _fonts.end()) {
        this->LoadResources(text->GetFont(), type::FONT);
    }
    if (auto it = _texts.find(text->GetText()); it != _texts.end()) {
        it->second->setString(text->GetText());
        it->second->setCharacterSize(text->GetCharacterSize());
        it->second->setFont(*_fonts[text->GetFont()]);
        it->second->setFillColor(this->mapColor(text->GetColor()));
        it->second->setPosition(text->GetX(), text->GetY());
    }
    if (auto it = _texts.find(text->GetText()); it != _texts.end()) {
        this->_window.draw(*it->second);
    }
    (void)text;
}

void arc::display::SFML::DrawScore(const int& score, std::shared_ptr<arc::TextComponent>text)
{
    if (_fonts.find(text->GetFont()) == _fonts.end()) {
        LoadResources(text->GetFont(), type::FONT);
    }
    this->_scoretext->setString(text->GetText() + " : "+ std::to_string(score));
    this->_scoretext->setCharacterSize(text->GetCharacterSize());
    this->_scoretext->setFont(*_fonts[text->GetFont()]);
    this->_scoretext->setFillColor(this->mapColor(text->GetColor()));
    this->_scoretext->setPosition(10, 10);
    this->_window.draw(*_scoretext);
}

sf::Color arc::display::SFML::mapColor(arc::Colors color) const
{
    switch (color) {
        case arc::Colors::BLACK:
            return sf::Color::Black;
        case arc::Colors::WHITE:
            return sf::Color::White;
        case arc::Colors::RED:
            return sf::Color::Red;
        case arc::Colors::GREEN:
            return sf::Color::Green;
        case arc::Colors::BLUE:
            return sf::Color::Blue;
        case arc::Colors::YELLOW:
            return sf::Color(255, 255, 0);
        case arc::Colors::MAGENTA:
            return sf::Color(255, 0, 255);
        case arc::Colors::CYAN:
            return sf::Color(0, 255, 255);
        default:
            return sf::Color(0, 0, 0);
    }
}

std::pair<int, int> arc::display::SFML::GetMousePos() const
{
    return std::pair<int, int>();
}

arc::click arc::display::SFML::GetMouseState() const
{
    return arc::click::NOTHING;
}

Event arc::display::SFML::HandleEvent()
{
    this->_keyPressed = sf::Keyboard::Unknown;
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed) {
            this->_window.close();
        }
        if (this->_event.type == sf::Event::KeyPressed) {
            if (this->_event.key.code == sf::Keyboard::Escape) {
                return Event::ESCAPE;
            }
            if (this->_event.key.code == sf::Keyboard::Up) {
                return Event::UP;
            }
            if (this->_event.key.code == sf::Keyboard::Down) {
                return Event::DOWN;
            }
            if (this->_event.key.code == sf::Keyboard::Left) {
                return Event::LEFT;
            }
            if (this->_event.key.code == sf::Keyboard::Right) {
                return Event::RIGHT;
            }
            if (this->_event.key.code == sf::Keyboard::Enter) {
                return Event::ENTER;
            }
            if (this->_event.key.code == sf::Keyboard::BackSpace) {
                return Event::BACKSPACE;
            }
            if (this->_event.key.code == sf::Keyboard::Delete) {
                return Event::DELETE;
            }
            if (this->_event.key.code == sf::Keyboard::Q) {
                return Event::PREVIOUS_LIB;
            }
            if (this->_event.key.code == sf::Keyboard::D) {
                return Event::NEXT_LIB;
            }
            if (this->_event.key.code == sf::Keyboard::F){
                return Event::PREVIOUS_GAME;
            }
            if (this->_event.key.code == sf::Keyboard::H){
                return Event::NEXT_GAME;
            }
            if (this->_event.key.code == sf::Keyboard::R){
                return Event::RESET;
            }
            const sf::Keyboard::Key keycode = this->_event.key.code;
            if (keycode >= sf::Keyboard::A && keycode <= sf::Keyboard::Z) {
                this->_keyPressed = keycode;
            }
            return Event::TEXT_INPUT;
        }
    }
    return Event::TEXT_INPUT;
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

void arc::display::SFML::LoadResources(std::string filepath, type type)
{
    if (type == type::TEXTURE) {
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(filepath)) {
            throw std::runtime_error("Failed to load texture");
        }

        auto sprite = std::make_unique<sf::Sprite>(*texture);
        _textures[filepath] = std::move(texture);
        _sprites[filepath] = std::move(sprite);
    } else if (type == type::FONT) {
        auto font = std::make_unique<sf::Font>();
        if (!font->loadFromFile(filepath)) {
            throw std::runtime_error("Failed to load font");
        }
        _fonts[filepath] = std::move(font);
        std::cout << "Font loaded: " << filepath << std::endl;
    } else if (type == type::TEXT) {
        auto text = std::make_unique<sf::Text>();
        _texts[filepath] = std::move(text);
    }
}

void arc::display::SFML::UnloadResources(std::string filepath, type type)
{
    if (type == type::TEXTURE) {
        _textures.erase(filepath);
        _sprites.erase(filepath);
    } else if (type == type::FONT) {
        _fonts.erase(filepath);
    } else if (type == type::TEXT) {
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


void arc::display::SFML::changeMenu(std::shared_ptr<arc::MenuComponent> menu)
{
    _texts.clear();

    int y = (_window.getSize().y / 2) - (menu->GetItems().size() * 30) / 2;
    int x = (_window.getSize().x / 2) - (menu->GetTitle()->GetText().size() * 10) / 2;

    this->LoadResources(menu->GetTitle()->GetText(), type::TEXT);
    if (menu->GetTitle()->GetFont() != "" && _fonts.find(menu->GetTitle()->GetFont()) == _fonts.end()) {
        this->LoadResources(menu->GetTitle()->GetFont(), type::FONT);
    }
    if (auto it = _texts.find(menu->GetTitle()->GetText()); it != _texts.end()) {
        it->second->setString(menu->GetTitle()->GetText());
        it->second->setCharacterSize(menu->GetTitle()->GetCharacterSize());
        it->second->setFont(*_fonts[menu->GetTitle()->GetFont()]);
        it->second->setFillColor(sf::Color::Red);
        it->second->setPosition(x, y);
    }
    y += 50;

    for (const auto& item : menu->GetItems()) {
        this->LoadResources(item->GetText(), type::TEXT);
        if (auto it = _texts.find(item->GetText()); it != _texts.end()) {
            it->second->setString(item->GetText());
            it->second->setCharacterSize(item->GetCharacterSize());
            it->second->setFont(*_fonts[item->GetFont()]);
            it->second->setPosition(x, y);
            it->second->setFillColor(item->GetText() == menu->GetSelectedItem()->GetText() ? 
                                   sf::Color::Green : sf::Color::White);
            y += 30;
        }
    }
}

void arc::display::SFML::changeMap(const std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map)
{
    int middle = (this->_window.getSize().x / 2) - (map[0].size() * 10) / 2;
    this->_rectangles.clear();
    for (const auto& row : map) {
        for (const auto& component : row) {
            sf::RectangleShape rectangle(sf::Vector2f(10, 10));
            rectangle.setPosition(((component->GetY() * 10) + middle), (component->GetX() * 10) + middle);
            if (component->GetType() == arc::TypeComponent::WALL) {
                rectangle.setFillColor(sf::Color::Red);
            } else if (component->GetType() == arc::TypeComponent::PLAYER) {
                rectangle.setFillColor(sf::Color::Green);
            } else if (component->GetType() == arc::TypeComponent::ENEMY) {
                rectangle.setFillColor(sf::Color::Blue);
            } else if (component->GetType() == arc::TypeComponent::COLLECTIBLE) {
                rectangle.setFillColor(sf::Color::Yellow);
            } else {
                rectangle.setFillColor(sf::Color::White);
            }
            _rectangles.push_back(rectangle);
        }
    }
}