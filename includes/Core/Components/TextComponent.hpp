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
    /**
     * @brief A component for displaying text with position, color, font, and size.
     */
    class TextComponent {
    public:
        /**
         * @brief Constructs a TextComponent with given position, text content, and color.
         * 
         * @param x X position of the text.
         * @param y Y position of the text.
         * @param text The string to display.
         * @param color The color of the text (default: UNDEFINED).
         */
        TextComponent(int x, int y, const std::string& text, Colors color = UNDEFINED);

        /**
         * @brief Gets the X position of the text.
         * 
         * @return int X coordinate.
         */
        int GetX() const;

        /**
         * @brief Gets the Y position of the text.
         * 
         * @return int Y coordinate.
         */
        int GetY() const;

        /**
         * @brief Gets the current text content.
         * 
         * @return const std::string& The text to display.
         */
        const std::string& GetText() const;

        /**
         * @brief Gets the path to the font file.
         * 
         * @return const std::string& Font file path.
         */
        const std::string& GetFont() const;

        /**
         * @brief Gets the size of the characters.
         * 
         * @return int Character size.
         */
        int GetCharacterSize() const;

        /**
         * @brief Sets the font file path.
         * 
         * @param font Path to the font file.
         */
        void SetFont(const std::string& font);

        /**
         * @brief Gets the color of the text.
         * 
         * @return Colors Enum representing the color.
         */
        Colors GetColor() const;

        /**
         * @brief Sets the X position of the text.
         * 
         * @param x New X coordinate.
         */
        void SetX(int x);

        /**
         * @brief Sets the Y position of the text.
         * 
         * @param y New Y coordinate.
         */
        void SetY(int y);

        /**
         * @brief Sets the text content to display.
         * 
         * @param text New text string.
         */
        void SetText(const std::string& text);

        /**
         * @brief Sets the size of the characters.
         * 
         * @param size New character size.
         */
        void SetCharacterSize(int size);

        /**
         * @brief Sets the color of the text.
         * 
         * @param color New text color.
         */
        void SetColor(Colors color);

    private:
        int X; ///< X coordinate of the text.
        int Y; ///< Y coordinate of the text.
        std::string Text; ///< The actual text to be displayed.
        Colors Color; ///< The color of the text.
        std::string FontPath; ///< Path to the font used.
        int CharacterSize; ///< Size of the characters in the text.
    };
}

#endif
