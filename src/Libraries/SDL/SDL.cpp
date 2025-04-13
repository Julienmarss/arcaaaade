/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** SDL.cpp
*/

#include "Libraries/SDL/SDL.hpp"
#include "Libraries/SDL/SDLWrapper.hpp"
#include <iostream>

extern "C" void *entryPoint() {
    return new arc::display::SDL();
}

arc::display::SDL::SDL() : _window(nullptr), _renderer(nullptr), _isOpen(false), _keyPressed(0)
{
    _textColor = {255, 255, 255, 255};
}

arc::display::SDL::~SDL()
{
    Close();
}

void arc::display::SDL::Initialize()
{
    SDLWrapper::init();
    std::cout << "SDL initialized" << std::endl;
}

void arc::display::SDL::Open()
{
    _window = SDLWrapper::createWindow("Arcade - SDL", 800, 600);
    _renderer = SDLWrapper::createRenderer(_window);
    SDLWrapper::setDrawColor(_renderer, 0, 0, 0, 255);
    _isOpen = true;
    std::cout << "SDL window opened" << std::endl;
}

void arc::display::SDL::Close()
{
    for (auto& pair : _textures) {
        if (pair.second) {
            SDLWrapper::destroyTexture(pair.second);
        }
    }
    _textures.clear();
    
    for (auto& pair : _fonts) {
        if (pair.second) {
            SDLWrapper::destroyFont(pair.second);
        }
    }
    _fonts.clear();
    SDLWrapper::cleanup(_window, _renderer);
    _isOpen = false;
    _window = nullptr;
    _renderer = nullptr;
}

bool arc::display::SDL::IsOpen()
{
    return _isOpen;
}

void arc::display::SDL::Display()
{
    SDLWrapper::presentRenderer(_renderer);
}

void arc::display::SDL::Clear()
{
    SDLWrapper::setDrawColor(_renderer, 0, 0, 0, 255);
    SDLWrapper::clearRenderer(_renderer);
}

void arc::display::SDL::DrawComponent(std::shared_ptr<arc::RenderComponent> component)
{
    SDL_Rect rect;
    SDL_Color color;
    
    rect.x = component->GetY() * 20;
    rect.y = component->GetX() * 20;
    rect.w = 18;
    rect.h = 18;
    
    switch (component->GetType()) {
        case arc::TypeComponent::WALL:
            color = {255, 0, 0, 255};
            break;
        case arc::TypeComponent::PLAYER:
            color = {0, 255, 0, 255};
            break;
        case arc::TypeComponent::ENEMY:
            color = {0, 0, 255, 255};
            break;
        case arc::TypeComponent::COLLECTIBLE:
            color = {255, 255, 0, 255};
            break;
        default:
            color = {50, 50, 50, 255};
            break;
    }
    
    SDLWrapper::setDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDLWrapper::fillRect(_renderer, rect);
}

void arc::display::SDL::DrawComponents(std::vector<std::shared_ptr<arc::RenderComponent>> components)
{
    for (const auto& component : components) {
        DrawComponent(component);
    }
}

void arc::display::SDL::DrawMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map)
{   
    int mapWidth = map[0].size() * 20;
    int mapHeight = map.size() * 20;
    int startX = (800 - mapWidth) / 2;
    int startY = (600 - mapHeight) / 2;
    
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            SDL_Rect rect = {startX + (int)j * 20, startY + (int)i * 20, 18, 18};
            
            SDL_Color color;
            switch (map[i][j]->GetType()) {
                case arc::TypeComponent::WALL:
                    color = {255, 0, 0, 255};
                    break;
                case arc::TypeComponent::PLAYER:
                    color = {0, 255, 0, 255};
                    break;
                case arc::TypeComponent::ENEMY:
                    color = {0, 0, 255, 255};
                    break;
                case arc::TypeComponent::COLLECTIBLE:
                    color = {255, 255, 0, 255};
                    break;
                default:
                    color = {50, 50, 50, 255};
                    break;
            }
            SDLWrapper::setDrawColor(_renderer, color.r, color.g, color.b, color.a);
            SDLWrapper::fillRect(_renderer, rect);
        }
    }
}

void arc::display::SDL::DrawMenu(std::shared_ptr<arc::MenuComponent> menu)
{
    try {
        if (_fonts.find(menu->GetTitle()->GetFont()) == _fonts.end()) {
            LoadResources(menu->GetTitle()->GetFont(), type::FONT);
        }

        std::vector<std::string> items;
        for (const auto& item : menu->GetItems()) {
            items.push_back(item->GetText());
        }

        SDL_Color titleColor = SDLWrapper::createColor(255, 0, 0); 
        SDL_Color normalColor = SDLWrapper::createColor(255, 255, 255);
        SDL_Color selectedColor = SDLWrapper::createColor(0, 255, 0); 

        int windowWidth = 800;
        int startX = (windowWidth - 200) / 2; 
        int startY = 50;

        SDLWrapper::drawMenu(
            _renderer,
            _fonts[menu->GetTitle()->GetFont()],
            menu->GetTitle()->GetText(),
            items,
            menu->GetSelectedItem()->GetText(),
            startX, startY,
            titleColor,
            normalColor,
            selectedColor
        );

        SDLWrapper::presentRenderer(_renderer);
    } catch (const std::exception& e) {
        std::cerr << "Error drawing menu: " << e.what() << std::endl;
    }
}
void arc::display::SDL::DrawText(std::shared_ptr<arc::TextComponent>text)
{
    try {
        if (_fonts.find(text->GetFont()) == _fonts.end()) {
            LoadResources(text->GetFont(), type::FONT);
        }
        
        SDL_Color color = SDLWrapper::createColor(
            text->GetColor() == Colors::RED ? 255 : 255,
            text->GetColor() == Colors::GREEN ? 255 : 255,
            text->GetColor() == Colors::BLUE ? 255 : 255
        );
        SDLWrapper::drawText(_renderer, _fonts[text->GetFont()],
                            text->GetText(), color,
                            text->GetX(), text->GetY());
    } catch (const std::exception& e) {
        std::cerr << "Error drawing text: " << e.what() << std::endl;
    }
}

void arc::display::SDL::DrawScore(const int& score, std::shared_ptr<arc::TextComponent>text)
{
    try {
        if (_fonts.find(text->GetFont()) == _fonts.end()) {
            LoadResources(text->GetFont(), type::FONT);
        }
        
        SDL_Color color = SDLWrapper::createColor(
            text->GetColor() == Colors::RED ? 255 : 255,
            text->GetColor() == Colors::GREEN ? 255 : 255,
            text->GetColor() == Colors::BLUE ? 255 : 255
        );
        
        SDLWrapper::drawScore(_renderer, _fonts[text->GetFont()],
                            score, text->GetText(), color,
                            text->GetX(), text->GetY());
    } catch (const std::exception& e) {
        std::cerr << "Error drawing score: " << e.what() << std::endl;
    }
}

std::pair<int, int> arc::display::SDL::GetMousePos() const
{
    return {0, 0};
}

arc::click arc::display::SDL::GetMouseState() const
{
    return arc::click::NOTHING;
}

Event arc::display::SDL::HandleEvent()
{
    _keyPressed = 0;
    
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            _isOpen = false;
            return Event::ESCAPE;
        }
        
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_UP:
                    return Event::UP;
                case SDLK_DOWN:
                    return Event::DOWN;
                case SDLK_LEFT:
                    return Event::LEFT;
                case SDLK_RIGHT:
                    return Event::RIGHT;
                case SDLK_RETURN:
                    return Event::ENTER;
                case SDLK_ESCAPE:
                    return Event::ESCAPE;
                case SDLK_SPACE:
                    return Event::SPACE;
                case SDLK_BACKSPACE:
                    return Event::BACKSPACE;
                case SDLK_DELETE:
                    return Event::DELETE;
                case SDLK_r:
                    return Event::RESET;
                case SDLK_q:
                    return Event::PREVIOUS_LIB;
                case SDLK_d:
                    return Event::NEXT_LIB;
                case SDLK_f:
                    return Event::NEXT_GAME;
                case SDLK_s:
                    return Event::PREVIOUS_GAME;
                
                default:
                    if (_event.key.keysym.sym >= SDLK_a && _event.key.keysym.sym <= SDLK_z) {
                        _keyPressed = 'a' + (_event.key.keysym.sym - SDLK_a);
                        return Event::TEXT_INPUT;
                    } else if (_event.key.keysym.sym >= SDLK_0 && _event.key.keysym.sym <= SDLK_9) {
                        _keyPressed = '0' + (_event.key.keysym.sym - SDLK_0);
                        return Event::TEXT_INPUT;
                    }
                    break;
            }
        }
    }
    
    return Event::TEXT_INPUT;
}

char arc::display::SDL::GetKeyPressed()
{
    return _keyPressed;
}

std::string arc::display::SDL::GetName() const
{
    return _name;
}

void arc::display::SDL::LoadResources(std::string filepath, type type)
{
    if (type == type::FONT) {
        if (_fonts.find(filepath) != _fonts.end()) {
            return;
        }
        std::cout << "Loading font: " << filepath << std::endl;
        TTF_Font* font = SDLWrapper::loadFont(filepath, 16);
        _fonts[filepath] = font;
    }
}

void arc::display::SDL::UnloadResources(std::string filepath, type type)
{
    if (type == type::FONT) {
        auto it = _fonts.find(filepath);
        if (it != _fonts.end()) {
            SDLWrapper::destroyFont(it->second);
            _fonts.erase(it);
        }
    } else if (type == type::TEXTURE) {
        auto it = _textures.find(filepath);
        if (it != _textures.end()) {
            SDLWrapper::destroyTexture(it->second);
            _textures.erase(it);
        }
    }
}

void arc::display::SDL::LaunchMusic(std::string filepath)
{
    (void)filepath;
}

void arc::display::SDL::StopMusic(std::string filepath)
{
    (void)filepath;
}

SDL_Color arc::display::SDL::mapColor(arc::Colors color) const
{
    switch (color) {
        case arc::Colors::RED:
            return {255, 0, 0, 255};
        case arc::Colors::GREEN:
            return {0, 255, 0, 255};
        case arc::Colors::BLUE:
            return {0, 0, 255, 255};
        case arc::Colors::YELLOW:
            return {255, 255, 0, 255};
        case arc::Colors::WHITE:
            return {255, 255, 255, 255};
        case arc::Colors::BLACK:
            return {0, 0, 0, 255};
        default:
            return {255, 255, 255, 255};
    }
}