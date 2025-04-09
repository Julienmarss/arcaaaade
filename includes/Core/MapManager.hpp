/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MapManager.hpp
*/

#ifndef MAPMANAGER_HPP
# define MAPMANAGER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Core/Components/RenderComponent.hpp"

namespace arc {

    /**
     * @class MapManager
     * @brief Handles loading, unloading, and managing renderable game maps.
     */
    class MapManager {
    public:
        /**
         * @brief Constructs a new MapManager.
         */
        MapManager();

        /**
         * @brief Destroys the MapManager and clears all maps.
         */
        ~MapManager();

        /**
         * @brief Loads a map from a file and stores it with a given name.
         * 
         * @param name Unique name to reference the map.
         * @param filepath Path to the map file.
         */
        void LoadMap(const std::string &name, const std::string& filepath);

        /**
         * @brief Unloads the map associated with the given name.
         * 
         * @param name Name of the map to remove.
         */
        void UnloadMap(const std::string &name);

        /**
         * @brief Retrieves the map by name.
         * 
         * @param name Name of the map to retrieve.
         * @return A 2D vector of RenderComponents representing the map.
         */
        std::vector<std::vector<arc::RenderComponent>> getMap(const std::string &name) const;

    private:
        /// Stores loaded maps identified by name.
        std::map<std::string, std::vector<std::vector<arc::RenderComponent>>> _maps;

        /**
         * @brief Creates a RenderComponent from position and character.
         * 
         * @param x X coordinate.
         * @param y Y coordinate.
         * @param c Character representing the component.
         * @return The created RenderComponent.
         */
        arc::RenderComponent createComponent(int x, int y, char c);
    };

}

#endif // MAPMANAGER_HPP
