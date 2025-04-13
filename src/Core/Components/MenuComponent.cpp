/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuComponent.cpp
*/

#include "Core/Components/MenuComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include <iostream>

arc::MenuComponent::MenuComponent()
    : selectedIndex(0), title(std::make_shared<arc::TextComponent>(0, 0, "", arc::Colors::WHITE))
{
}
void arc::MenuComponent::AddItem(std::shared_ptr<arc::TextComponent> item)
{
    items.push_back(item);
}

void arc::MenuComponent::RemoveItem(std::shared_ptr<arc::TextComponent> item)
{
    if (items.empty() || item == nullptr) {
        return;
    }
    for (auto it = items.begin(); it != items.end(); ) {
        if (*it && (*it)->GetText() == item->GetText()) {
            it = items.erase(it);
        } else {
            ++it;
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

void arc::MenuComponent::SetTitle(std::shared_ptr<arc::TextComponent> menuTitle)
{
    title = menuTitle;
}

std::shared_ptr<arc::TextComponent> arc::MenuComponent::GetSelectedItem() const
{
    return items[selectedIndex];
}

std::shared_ptr<arc::TextComponent> arc::MenuComponent::GetTitle() const
{
    return title;
}

std::vector<std::shared_ptr<arc::TextComponent>>arc::MenuComponent::GetItems() const
{
    return items;
}
