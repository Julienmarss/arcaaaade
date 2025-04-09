/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuComponent.hpp
*/

#ifndef MENUCOMPONENT_HPP
# define MENUCOMPONENT_HPP

#include <string>
#include <vector>
#include <functional>
#include "Core/Components/TextComponent.hpp"

namespace arc {
    /**
     * @brief MenuComponent class - Class that represents a menu component with a title and a list of items
     */
    class MenuComponent {
        public:
            /**
             * @brief Construct a new MenuComponent object
             */
            MenuComponent();

            /**
             * @brief Destroy the MenuComponent object
             */
            ~MenuComponent() = default;

            /**
             * @brief Add an item to the menu
             * @param item The item to add
             */
            void AddItem(const TextComponent& item);

            /**
             * @brief Remove an item from the menu
             * @param item The item to remove
             */
            void RemoveItem(const TextComponent& item);

            /**
             * @brief Select an item from the menu
             * @param index The index of the item to select
             */
            void Select(int index);

            /**
             * @brief Set the title of the menu
             * @param menuTitle The title of the menu
             */
            void SetTitle(const TextComponent& menuTitle);

            /**
             * @brief Get the selected item from the menu
             * @return The selected item
             */
            TextComponent GetSelectedItem() const;

            /**
             * @brief Get selected index
             * @return The selected index
             */
            int GetSelectedIndex() const;

            /**
             * @brief Get the title of the menu
             * @return The title of the menu
             */
            TextComponent GetTitle() const;

            /**
             * @brief Get the items of the menu
             * @return The items of the menu
             */
            std::vector<TextComponent> GetItems() const;


        private:
            /**
             * @brief The items of the menu
             */
            std::vector<TextComponent> items;

            /**
             * @brief The selected index
             */
            int selectedIndex;

            /**
             * @brief The title of the menu
             */
            TextComponent title;
    };
}

#endif