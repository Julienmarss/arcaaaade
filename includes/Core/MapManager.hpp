/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MapManager.hpp
*/

#ifndef MAPMANAGER_HPP
# define MAPMANAGER_HPP

# include <iostream>
# include <vector>
# include <string>
#include <map>
#include "Core/Components/RenderComponent.hpp"

namespace arc {
    class MapManager {
        public:
            MapManager();
            ~MapManager();
            void LoadMap(const std::string &name, const std::string& filepath);
            void UnloadMap(const std::string &name);
            std::vector<std::vector<arc::RenderComponent>> getMap(const std::string &name) const;
        private:
            std::map<std::string, std::vector<std::vector<arc::RenderComponent>> > _maps;
            arc::RenderComponent createComponent(int x, int y, char c);
    };
}
#endif