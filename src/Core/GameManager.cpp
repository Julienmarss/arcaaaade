/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** GameManager.cpp
*/

#include "Core/GameManager.hpp"

arc::GameManager::GameManager() : _text(0, 0, "Score", arc::Colors::WHITE)
{
    _score = 0;
    _game = nullptr;
    _text.SetFont("ressources/font.ttf");
}
arc::GameManager::~GameManager()
{
}

void arc::GameManager::LoadGame(IGameLibrary *game)
{

    if (!game) {
        throw std::runtime_error("Null game pointer");
    }
    std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map = this->_mapManager.getMap(game->GetName());
    if (game->GetMap().size() == 0) {
        game->AddMap(map);
        game->InitGame();
    }
    _game = game;
    std::cout << "Game loaded: " << game->GetName() << std::endl;
}

void arc::GameManager::run()
{
}

std::shared_ptr<arc::TextComponent> arc::GameManager::getCurrentText() const
{
    return std::make_shared<arc::TextComponent>(_text);;
}

void arc::GameManager::ResetGame()
{
    std::cout << "Game reset" << std::endl;
    if (this->_game == nullptr) {
        throw std::runtime_error("Game is not loaded");
    }
    this->_game->Reset();
    this->_game->AddMap(this->_mapManager.getMap(this->_game->GetName()));
}