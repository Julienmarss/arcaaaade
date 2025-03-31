#ifndef RENDERCOMPONENT_HPP
# define RENDERCOMPONENT_HPP

#include "Core/Color.hpp"
#include <string>

namespace arc {

    enum TypeComponent {
        EMPTY = -1,
        WALL = 0,
        PLAYER = 1,
        ENEMY = 2,
        COLLECTIBLE = 3,
    };
    class RenderComponent {
    public:
        RenderComponent(int x_initial, int y_initial, TypeComponent type_initial,
                        char character_initial, const std::string& filePath_initial);
        int GetX() const;
        int GetY() const;
        TypeComponent GetType() const;
        char GetCharacter() const;
        std::string GetFilePath() const;
        void SetX(int x_setter);
        void SetY(int y_setter);
        void SetType(TypeComponent type_setter);
        void SetCharacter(char character_setter);
        void SetFilePath(std::string filePath_setter);
    private:
        int x_position;
        int y_position;
        TypeComponent type;
        char character;
        std::string filePath;
    };
}

#endif