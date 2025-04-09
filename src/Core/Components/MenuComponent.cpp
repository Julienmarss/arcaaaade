/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuComponent.cpp
*/

#include "Core/Components/MenuComponent.hpp"
#include "Core/Components/TextComponent.hpp"

arc::MenuComponent::MenuComponent()
    : selectedIndex(0), title(0, 0, "", arc::Colors::WHITE)
{
}
void arc::MenuComponent::AddItem(const arc::TextComponent& item)
{
    items.push_back(item);
}

void arc::MenuComponent::RemoveItem(const arc::TextComponent& item)
{
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->GetText() == item.GetText()) {
            items.erase(it);
            break;
        }
    }
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

void arc::MenuComponent::SetTitle(const arc::TextComponent& menuTitle)
{
    title = menuTitle;
}

arc::TextComponent arc::MenuComponent::GetSelectedItem() const
{
    return items[selectedIndex];
}

arc::TextComponent arc::MenuComponent::GetTitle() const
{
    return title;
}

std::vector<arc::TextComponent> arc::MenuComponent::GetItems() const
{
    return items;
}
