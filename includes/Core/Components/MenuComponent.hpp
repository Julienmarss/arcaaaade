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

namespace arc {
    class MenuComponent {
        public:
            MenuComponent() = default;
            ~MenuComponent() = default;
    
            void AddItem(const std::string& item);
            void RemoveItem(const std::string& item);
            void Select(int index);
            void SetTitle(const std::string& menuTitle);
    
            std::string GetSelectedItem() const;
            int GetSelectedIndex() const;
            std::string GetTitle() const;
            std::vector<std::string> GetItems() const;
            void ClearItems();
        private:
            std::vector<std::string> items;
            std::string title;
            int selectedIndex = 0;
        };
}

#endif