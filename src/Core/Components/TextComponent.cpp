/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** TextComponent.cpp
*/

#include "Core/Components/TextComponent.hpp"

arc::TextComponent::TextComponent(int x, int y, const std::string& text, Colors color)
    : X(x), Y(y), Text(text), Color(color), FontPath(), CharacterSize(16)
{
}
int arc::TextComponent::GetX() const
{
    return X;
}

int arc::TextComponent::GetY() const
{
    return Y;
}

const std::string& arc::TextComponent::GetText() const
{
    return Text;
}

arc::Colors arc::TextComponent::GetColor() const
{
    return Color;
}

void arc::TextComponent::SetX(int x)
{
    X = x;
}
void arc::TextComponent::SetY(int y)
{
    Y = y;
}
void arc::TextComponent::SetText(const std::string& text)
{
    Text = text;
}
void arc::TextComponent::SetColor(Colors color)
{
    Color = color;
}

void arc::TextComponent::SetFont(const std::string& font)
{
    FontPath = font;
}

int arc::TextComponent::GetCharacterSize() const
{
    return CharacterSize;
}

void arc::TextComponent::SetCharacterSize(int size)
{
    CharacterSize = size;
}

const std::string& arc::TextComponent::GetFont() const
{
    return FontPath;
}