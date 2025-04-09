/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** RenderComponent.cpp
*/

#include "Core/Components/RenderComponent.hpp"
#include <string>
arc::RenderComponent::RenderComponent(int x_initial, int y_initial, TypeComponent type_initial,
                        char character_initial, const std::string& filePath_initial)
{
    x_position = x_initial;
    y_position = y_initial;
    type = type_initial;
    character = character_initial;
    filePath = filePath_initial;
}

int arc::RenderComponent::GetX() const
{
    return x_position;
}

int arc::RenderComponent::GetY() const
{
    return y_position;
}

arc::TypeComponent arc::RenderComponent::GetType() const
{
    return type;
}

char arc::RenderComponent::GetCharacter() const
{
    return character;
}

std::string arc::RenderComponent::GetFilePath() const
{
    return filePath;
}

void arc::RenderComponent::SetX(int x_setter)
{
    x_position = x_setter;
}

void arc::RenderComponent::SetY(int y_setter)
{
    y_position = y_setter;
}

void arc::RenderComponent::SetType(TypeComponent type_setter)
{
    type = type_setter;
}

void arc::RenderComponent::SetCharacter(char character_setter)
{
    character = character_setter;
}
void arc::RenderComponent::SetFilePath(std::string filePath_setter)
{
    filePath = filePath_setter;
}