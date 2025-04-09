#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

#include "Core/Abstract/AGraphicLibrary.hpp"
#include "Core/Abstract/AGameLibrary.hpp"
#include "Core/MapManager.hpp"

namespace arc {

    /**
     * @class GameManager
     * @brief Manages the state, logic, and flow of a game session.
     * 
     * Handles the interaction between the game logic, graphical library, and player session data,
     * such as the score and game map.
     */
    class GameManager {
    public:
        /**
         * @brief Constructs a new GameManager instance.
         */
        GameManager();

        /**
         * @brief Destroys the GameManager instance.
         */
        ~GameManager();

        /**
         * @brief Loads a game and initializes the player session.
         * 
         * @param username Name of the player.
         * @param game Pointer to the game library to load.
         * @param library Pointer to the graphical library to use.
         */
        void LoadGame(const std::string &username, IGameLibrary *game, IGraphicLibrary *library);

        /**
         * @brief Starts and runs the game loop.
         */
        void run();

        /**
         * @brief Gets the current renderable game map.
         * 
         * @return A 2D vector representing the current map using RenderComponents.
         */
        std::vector<std::vector<arc::RenderComponent>> getCurrentMap() const;

        /**
         * @brief Gets the current game score.
         * 
         * @return The current score as an integer.
         */
        int getCurrentScore() const;

        /**
         * @brief Gets the current text for score display
         * 
         * @return The current TextComponent.
         */
        TextComponent getCurrentText() const;

    private:
        int _score;                              ///< Current player score.
        MapManager _mapManager;                  ///< Handles the current game map.
        arc::IGameLibrary *_game;                ///< Pointer to the loaded game logic.
        arc::TextComponent _text;                ///< Current text to be displayed.
    };

}

#endif // GAMEMANAGER_HPP
