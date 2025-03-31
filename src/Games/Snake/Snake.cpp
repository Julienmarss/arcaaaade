/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Snake.cpp
*/
#include "Games/Snake/Snake.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/Click.hpp"
#include "Core/Event.hpp"
#include "Core/Components/RenderComponent.hpp"
#include <vector>

extern "C" void *entryPoint() {
    return new arc::games::Snake();
}

arc::games::Snake::Snake()
{
}

arc::games::Snake::~Snake()
{
}

bool arc::games::Snake::Update(click state, Event key)
{
    (void)state;
    (void)key;
    return false;
}

void arc::games::Snake::AddObject(std::string name, arc::RenderComponent)
{
    (void)name;
}

void arc::games::Snake::DeleteObject(std::string name)
{
    (void)name;
}

std::vector<arc::RenderComponent> arc::games::Snake::GetObjects(std::string name) const
{
    (void)name;
    return std::vector<arc::RenderComponent>();
}

int arc::games::Snake::GetScore() const
{
    return 0;
}

bool arc::games::Snake::IsGameOver() const
{
    return false;
}

void arc::games::Snake::Reset()
{
}

std::string arc::games::Snake::GetName() const
{
    return "Snake";
}

void arc::games::Snake::InitGame()
{
}

void arc::games::Snake::CloseGame()
{
}

