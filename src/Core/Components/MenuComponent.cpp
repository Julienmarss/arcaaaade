/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuComponent.cpp
*/

#include "Core/Components/MenuComponent.hpp"


void arc::MenuComponent::AddItem(const std::string& item)
{
    items.push_back(item);
}

void arc::MenuComponent::RemoveItem(const std::string& item)
{
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void arc::MenuComponent::Select(int index)
{
    size_t size = items.size();
    if (index < 0) {
        selectedIndex = size - 1;
    } else if (static_cast<size_t>(index) >= size) {
        selectedIndex = 0;
    } else {
        selectedIndex = index;
    }
}

int arc::MenuComponent::GetSelectedIndex() const
{
    return selectedIndex;
}

void arc::MenuComponent::SetTitle(const std::string& menuTitle)
{
    title = menuTitle;
}

std::string arc::MenuComponent::GetSelectedItem() const
{
    return items[selectedIndex];
}

std::string arc::MenuComponent::GetTitle() const
{
    return title;
}

std::vector<std::string> arc::MenuComponent::GetItems() const
{
    return items;
}
