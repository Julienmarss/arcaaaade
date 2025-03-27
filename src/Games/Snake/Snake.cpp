/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Snake.cpp
*/
#include "Games/Snake/Snake.hpp"
#include "Interface/IGameModule.hpp"

extern "C" arc::IGameModule *entryPoint()
{
    return new arc::games::Snake;
}

arc::games::Snake::Snake()
{
}

arc::games::Snake::~Snake()
{
}

void arc::games::Snake::initGame()
{
}

void arc::games::Snake::updateGame()
{
}

void arc::games::Snake::displayGame()
{
}