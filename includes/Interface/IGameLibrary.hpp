/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** IGameLibrary.hpp
*/

#ifndef IGAMELIBRARY_HPP
# define IGAMELIBRARY_HPP

#include <string>
#include <vector>
#include <map>
#include "Core/Click.hpp"
#include "Core/Event.hpp"
#include "Core/Components/RenderComponent.hpp"

namespace arc {

    enum GameState {
    };

    class IGameLibrary {
    public:
        /**
         * @brief Destroy the IGameLibrary object
         */
        virtual ~IGameLibrary() = default;

        /**
         * @brief Update the game
         * @param state The state of the mouse
         * @param key The key pressed
         */
        virtual bool Update(click state, Event key) = 0;

        /**
         * @brief Add an object to the game
         * @param name The name of the object
         * @param component The component of the object
         */
        virtual void AddObject(std::string name, RenderComponent component) = 0;

        /**
         * @brief Delete an object from the game
         * @param name The name of the object
         */
        virtual void DeleteObject(std::string name) = 0;

        /**
         * @brief Get the objects of the game
         * @param name The name of the object
         * @return The objects of the game
         */
        virtual std::vector<RenderComponent> GetObjects(std::string name) const = 0;

        /**
         * @brief Get the score of the game
         * @return The score of the game
         */
        virtual bool IsGameOver() const = 0;

        /**
         * @brief Reset the game
         */
        virtual void Reset() = 0;

        /**
         * @brief Get the name of the game
         * @return The name of the game
         */
        virtual std::string GetName() const = 0;

        /**
         * @brief Initialize the game
         */
        virtual void InitGame() = 0;

        /**
         * @brief Close the game
         */
        virtual void CloseGame() = 0;

        /**
         * @brief Add a map to the game
         * @param map The map of the game
         */
        virtual void AddMap(std::vector<std::vector<RenderComponent>> map) = 0;

        /**
         * @brief Get the map of the game
         * @return The map of the game
         */
        virtual std::vector<std::vector<RenderComponent>> GetMap() const = 0;
        /**
         * @brief Get the score of the game
         * @return The score of the game
         */
        virtual int GetScore() const = 0;
    };
}

#endif