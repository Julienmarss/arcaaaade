#ifndef RENDERCOMPONENT_HPP
# define RENDERCOMPONENT_HPP

#include "Core/Color.hpp"
#include <string>

namespace arc {
    /**
     * @brief Enum that represents the type of a component
     */
    enum TypeComponent {
        EMPTY = -1,
        WALL = 0,
        PLAYER = 1,
        ENEMY = 2,
        COLLECTIBLE = 3,
    };

    /**
     * @brief RenderComponent class - Class that represents a render component with a position, a type, a character and a file path
     */
    class RenderComponent {
        public:
        /**
         * @brief Construct a new RenderComponent object
         * @param x_initial The initial x position
         * @param y_initial The initial y position
         * @param type_initial The initial type
         * @param character_initial The initial character
         * @param filePath_initial The initial file path
         */
        RenderComponent(int x_initial, int y_initial, TypeComponent type_initial, 
                       char character_initial, const std::string& filePath_initial);

        /**
         * @brief Get the x position of the component
         * @return The x position
         */
        int GetX() const;

        /**
         * @brief Get the y position of the component
         * @return The y position
         */
        int GetY() const;

        /**
         * @brief Get the type of the component
         * @return The type
         */
        TypeComponent GetType() const;
        /**
         * @brief Set type of the component
         * @param type_setter The type to set
         */
        void SetType(TypeComponent type_setter);

        /**
         * @brief Get the character of the component
         * @return The character
         */
        char GetCharacter() const;

        /**
         * @brief Get the file path of the component
         * @return The file path
         */
        std::string GetFilePath() const;

        /**
         * @brief Set the character of the component
         * @param character_setter The character to set
         */
        void SetCharacter(char character_setter);

        /**
         * @brief Set the file path of the component
         * @param filePath_setter The file path to set
         */
        void SetFilePath(std::string filePath_setter);

        /**
         * @brief Set the x position of the component
         * @param x_setter The x position to set
         */
        void SetX(int x_setter);

        /**
         * @brief Set the y position of the component
         * @param y_setter The y position to set
         */
        void SetY(int y_setter);

    private:
        /**
         * @brief The x position of the component
         */
        int x_position;

        /**
         * @brief The y position of the component
         */
        int y_position;

        /**
         * @brief The type of the component
         */
        TypeComponent type;

        /**
         * @brief The character of the component
         */
        char character;

        /**
         * @brief The file path of the component
         */
        std::string filePath;
    };
}

#endif