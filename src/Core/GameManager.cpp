/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** GameManager.cpp
*/

#include "Core/GameManager.hpp"

arc::GameManager::GameManager() : _text(0, 0, "Score : 0", arc::Colors::WHITE)
{
    _score = 0;
}
arc::GameManager::~GameManager()
{
}

void arc::GameManager::LoadGame(const std::string &username, IGameLibrary *game, IGraphicLibrary *library)
{
    this->_game = game;
    std::vector<std::vector<arc::RenderComponent>> map = this->_mapManager.getMap(game->GetName());
    game->AddMap(map);
    game->InitGame();
    (void)username;
    (void)library;
}

void arc::GameManager::run()
{
}

arc::TextComponent arc::GameManager::getCurrentText() const
{
    return _text;
}