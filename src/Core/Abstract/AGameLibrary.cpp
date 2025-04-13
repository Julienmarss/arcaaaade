/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** AGameLibrary.cpp
*/

#include "Core/Abstract/AGameLibrary.hpp"
#include "Core/Components/RenderComponent.hpp"
#include <map>
#include <memory>

bool arc::games::AGameLibrary::IsGameOver() const 
{
    return _gameOver;
}

int arc::games::AGameLibrary::GetScore() const
{
    return _score;
}

void arc::games::AGameLibrary::AddObject(std::string name, std::shared_ptr<arc::RenderComponent> object)
{
    _objects[name].push_back(object);
}

std::string arc::games::AGameLibrary::GetName() const
{
    return _gameName;
}
void arc::games::AGameLibrary::DeleteObject(std::string name)
{
    _objects.erase(name);
}

std::vector<std::shared_ptr<arc::RenderComponent>> arc::games::AGameLibrary::GetObjects(std::string name) const
{
    return _objects.at(name);
}

void arc::games::AGameLibrary::AddMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map)
{
    _map = map;
}

std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> arc::games::AGameLibrary::GetMap() const
{
    return _map;
}