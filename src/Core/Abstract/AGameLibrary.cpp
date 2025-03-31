/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** AGameLibrary.cpp
*/

#include "Core/Abstract/AGameLibrary.hpp"
#include "Core/Components/IObject.hpp"
#include "Core/Components/RenderComponent.hpp"
#include <map>

bool arc::games::AGameLibrary::IsGameOver() const 
{
    return _gameOver;
}

int arc::games::AGameLibrary::GetScore() const
{
    return _score;
}

void arc::games::AGameLibrary::AddObject(std::string name, arc::RenderComponent object)
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

std::vector<arc::RenderComponent> arc::games::AGameLibrary::GetObjects(std::string name) const
{
    return _objects.at(name);
}