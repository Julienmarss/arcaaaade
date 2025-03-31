/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** TextComponent.hpp
*/

#ifndef TEXTCOMPONENT_HPP
# define TEXTCOMPONENT_HPP

#include <string>
#include "Core/Color.hpp"
namespace arc {
    class TextComponent {
    public:
        TextComponent(int x, int y, const std::string& text, Colors color = UNDEFINED);
        int GetX() const;
        int GetY() const;
        const std::string& GetText() const;
        Colors GetColor() const;
        void SetX(int x);
        void SetY(int y);
        void SetText(const std::string& text);
        void SetColor(Colors color);
    private:
        int X;
        int Y;
        std::string Text;
        Colors Color;
    };
}

#endif