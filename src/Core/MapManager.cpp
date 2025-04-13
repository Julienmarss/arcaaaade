/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MapManager.cpp
*/

#include "Core/MapManager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <memory>

arc::MapManager::MapManager()
{
    this->LoadMap("snake", "ressources/maps/snake1.txt");
    this->LoadMap("nibbler", "ressources/maps/nibbler1.txt");
}

arc::MapManager::~MapManager()
{
    for (auto &map : _maps) {
        map.second.clear();
    }
    _maps.clear();
}

void arc::MapManager::LoadMap(const std::string &name, const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open map " + filepath +"file");
        return;
    }
    std::string line;
    std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map;
    int lineIndex = 0;
    while (std::getline(file, line)) {
        std::vector<std::shared_ptr<arc::RenderComponent>> lineComponents;
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c != '\n' && c != '\r') {
                lineComponents.push_back(createComponent(lineIndex, i, c));
            }
        }
        map.push_back(lineComponents);
        lineIndex++;
    }
    _maps[name] = map;
    file.close();
}

std::shared_ptr<arc::RenderComponent> arc::MapManager::createComponent(int x, int y, char c)
{
    if (c == ' ')
        return std::make_shared<arc::RenderComponent>(x, y, arc::TypeComponent::EMPTY, c, "ressources/empty.png");
    if (c == '#')
        return std::make_shared<arc::RenderComponent>(x, y, arc::TypeComponent::WALL, c, "ressources/wall.png");
    if (c == 'P')
        return std::make_shared<arc::RenderComponent>(x, y, arc::TypeComponent::PLAYER, c, "ressources/player.png");
    if (c == 'E')
        return std::make_shared<arc::RenderComponent>(x, y, arc::TypeComponent::ENEMY, c, "ressources/enemy.png");
    if (c == 'C' || c == 'F')
        return std::make_shared<arc::RenderComponent>(x, y, arc::TypeComponent::COLLECTIBLE, c, "ressources/collectible.png");
    return std::make_shared<arc::RenderComponent>(x, y, arc::TypeComponent::EMPTY, c, "ressources/empty.png");
}

std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> arc::MapManager::getMap(const std::string &name) const
{
    std::string lowername = name;
    std::transform(lowername.begin(), lowername.end(), lowername.begin(), [](unsigned char c) { return std::tolower(c); });
    auto it = _maps.find(lowername);
    if (it != _maps.end()) {
        return it->second;
    }
    throw std::runtime_error("Map " + lowername + " not found");
}