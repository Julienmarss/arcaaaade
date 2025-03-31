/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** GameManager.cpp
*/

#include "Core/GameManager.hpp"

arc::GameManager::GameManager()
{
    _score = 0;
}
arc::GameManager::~GameManager()
{
}

void arc::GameManager::LoadGame(const std::string &username, IGameLibrary *game)
{
    _score = 0;
    game->InitGame(); 
    game->CloseGame();
    this->_map = this->_mapManager.getMap(game->GetName());
    (void) username;
}

void arc::GameManager::run()
{
}

std::vector<std::vector<arc::RenderComponent>> arc::GameManager::getCurrentMap() const
{
    return _map;
}

int arc::GameManager::getCurrentScore() const
{
    return _score;
}

void arc::GameManager::displayMap()
{
    for (auto &line : _map) {
        for (auto &component : line) {
            std::cout << component.GetCharacter();
        }
        std::cout << std::endl;
    }
}