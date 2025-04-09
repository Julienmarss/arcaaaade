/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Snake.hpp
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "Core/Abstract/AGameLibrary.hpp"
#include "Core/Click.hpp"
#include "Core/Event.hpp"

namespace arc::games {

    /**
     * @class Snake
     * @brief Snake game implementation derived from AGameLibrary.
     * 
     * This class contains the logic and state management for the classic Snake game.
     */
    class Snake : public AGameLibrary {
    public:
        /**
         * @brief Constructs a new Snake game instance.
         */
        Snake();

        /**
         * @brief Destructs the Snake game instance.
         */
        ~Snake();

        /**
         * @brief Updates the game state based on input and tick.
         * 
         * @param state The click state (if used).
         * @param key The event key pressed.
         * @return True if update succeeded or game should continue, false if it should quit.
         */
        bool Update(click state, Event key);

        /**
         * @brief Adds a renderable object to the game.
         * 
         * @param name Name identifier for the object group.
         * @param component The RenderComponent to add.
         */
        void AddObject(std::string name, arc::RenderComponent component);

        /**
         * @brief Deletes a group of objects by name.
         * 
         * @param name Name identifier of the group to delete.
         */
        void DeleteObject(std::string name);

        /**
         * @brief Gets the renderable objects associated with a name.
         * 
         * @param name Name of the group to retrieve.
         * @return A vector of RenderComponents.
         */
        std::vector<arc::RenderComponent> GetObjects(std::string name) const;

        /**
         * @brief Gets the current score.
         * 
         * @return The score as an integer.
         */
        int GetScore() const;

        /**
         * @brief Checks if the game is over.
         * 
         * @return True if the game is over, false otherwise.
         */
        bool IsGameOver() const;

        /**
         * @brief Resets the game to its initial state.
         */
        void Reset();

        /**
         * @brief Gets the name of the game.
         * 
         * @return The game's name as a string.
         */
        std::string GetName() const;

        /**
         * @brief Initializes the game.
         */
        void InitGame();

        /**
         * @brief Closes and cleans up the game state.
         */
        void CloseGame();

        /**
         * @brief Retrieves the game map for rendering.
         * 
         * @return A 2D vector of RenderComponents.
         */
        std::vector<std::vector<arc::RenderComponent>> GetMap() const override;

        /**
         * @brief Adds or sets the current game map.
         * 
         * @param map The new game map to use.
         */
        void AddMap(std::vector<std::vector<arc::RenderComponent>> map) override;

    private:
        std::map<std::string, std::vector<arc::RenderComponent>> _objects; ///< Game objects by name.
        std::vector<std::pair<int, int>> _snake;                           ///< Snake body positions.
        std::pair<int, int> _playerHead;                                   ///< Current position of snake's head.
        std::vector<std::vector<RenderComponent>> _map;                    ///< Current game map.
        int _score;                                                        ///< Player score.
        int _directionX;                                                   ///< Current movement direction X.
        int _directionY;                                                   ///< Current movement direction Y.

        /**
         * @brief Spawns food at a random valid position on the map.
         */
        void spawnFood();

        /**
         * @brief Checks if a position is valid (not a wall or snake body).
         * 
         * @param x X position.
         * @param y Y position.
         * @return True if the position is valid, false otherwise.
         */
        bool isValidPosition(int x, int y) const;

        /**
         * @brief Changes the position of the snake's head.
         * 
         * @param x New X position.
         * @param y New Y position.
         */
        void changePlayerPosition(int x, int y);

        /**
         * @brief Adds a new part to the snake at the specified position.
         * 
         * @param x X coordinate.
         * @param y Y coordinate.
         */
        void addSnakePart(int x, int y);
    };

}

/**
 * @brief External C-style entry point for loading the game dynamically.
 * 
 * @return A void pointer to the game instance.
 */
extern "C" void *entryPoint();

#endif // SNAKE_HPP_
