/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Nibbler.hpp
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "Core/Abstract/AGameLibrary.hpp"
#include "Core/Click.hpp"
#include "Core/Event.hpp"
#include <memory>

namespace arc::games {

    /**
     * @class Nibbler
     * @brief Nibbler game implementation derived from AGameLibrary.
     * 
     * This class contains the logic and state management for the Nibbler game.
     */
    class Nibbler : public AGameLibrary {
    public:
        /**
         * @brief Constructs a new Nibbler game instance.
         */
        Nibbler();

        /**
         * @brief Destructs the Nibbler game instance.
         */
        ~Nibbler();

        /**
         * @brief Updates the game state based on input and tick.
         * 
         * @param state The click state (if used).
         * @param key The event key pressed.
         * @return True if update succeeded or game should continue, false if it should quit.
         */
        bool Update(click state, Event key) override;

        /**
         * @brief Adds a renderable object to the game.
         * 
         * @param name Name identifier for the object group.
         * @param component The RenderComponent to add.
         */
        void AddObject(std::string name, std::shared_ptr<arc::RenderComponent> component) override;

        /**
         * @brief Deletes a group of objects by name.
         * 
         * @param name Name identifier of the group to delete.
         */
        void DeleteObject(std::string name) override;

        /**
         * @brief Gets the renderable objects associated with a name.
         * 
         * @param name Name of the group to retrieve.
         * @return A vector of RenderComponents.
         */
        std::vector<std::shared_ptr<arc::RenderComponent>> GetObjects(std::string name) const override;

        /**
         * @brief Gets the current score.
         * 
         * @return The score as an integer.
         */
        int GetScore() const override;

        /**
         * @brief Checks if the game is over.
         * 
         * @return True if the game is over, false otherwise.
         */
        bool IsGameOver() const override;

        /**
         * @brief Resets the game to its initial state.
         */
        void Reset() override;

        /**
         * @brief Gets the name of the game.
         * 
         * @return The game's name as a string.
         */
        std::string GetName() const override;

        /**
         * @brief Initializes the game.
         */
        void InitGame() override;

        /**
         * @brief Closes and cleans up the game state.
         */
        void CloseGame() override;

        /**
         * @brief Retrieves the game map for rendering.
         * 
         * @return A 2D vector of RenderComponents.
         */
        std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> GetMap() const override;

        /**
         * @brief Adds or sets the current game map.
         * 
         * @param map The new game map to use.
         */
        void AddMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map) override;

    private:
        std::vector<std::pair<int, int>> _snake;                           ///< Snake body positions.
        std::pair<int, int> _playerHead;                                   ///< Current position of snake's head.
        std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> _copy; ///< Copy of the initial map for Reset().
        int _directionX;                                                   ///< Current movement direction X.
        int _directionY;                                                   ///< Current movement direction Y.
        int _foodCount;                                                    ///< Count of remaining food items.
        bool _canTurn;                                                     ///< Flag indicating if player can turn.

        /**
         * @brief Spawns food at a valid position on the map.
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
         * @brief Checks if the position is an intersection.
         * 
         * @param x X position.
         * @param y Y position.
         * @return True if the position is an intersection, false otherwise.
         */
        bool isIntersection(int x, int y) const;

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

        /**
         * @brief Auto-turns the snake when encountering obstacles.
         * 
         * @param nextX Next X position to check.
         * @param nextY Next Y position to check.
         * @return True if direction was changed, false otherwise.
         */
        bool autoTurn(int nextX, int nextY);

        /**
         * @brief Count remaining food on the map.
         * 
         * @return Number of food items on the map.
         */
        int countFood() const;
    };

}

/**
 * @brief External C-style entry point for loading the game dynamically.
 * 
 * @return A void pointer to the game instance.
 */
extern "C" void *entryPoint();

#endif // NIBBLER_HPP_