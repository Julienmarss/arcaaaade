/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Application.hpp
*/

#ifndef APPLICATION_HPP
# define APPLICATION_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/ArcadeState.hpp"
#include "Core/MenuManager.hpp"
#include "Core/ToggleLibManager.hpp"
#include "Core/ScoreboardManager.hpp"
#include <memory>

namespace arc {
    /**
     * @brief Main application class for running the Arcade project.
     */
    class Application
    {
        public:
            /**
             * @brief Constructs the Application object with command-line arguments.
             * 
             * @param ac Argument count.
             * @param av Argument values.
             */
            Application(int ac, char **av);

            /**
             * @brief Destructor for Application.
             */
            ~Application();

            /**
             * @brief Runs the arcade application with the specified graphic library.
             * 
             */
            void run();

        private:
            /**
             * @brief Loads all available graphic libraries.
             */
            void getLibraries();

            /**
             * @brief Loads all available game libraries.
             */
            void getGames();

            /**
             * @brief Initializes the menu components.
             */
            void loadMenus();

            /**
             * @brief Reads the content of a directory and returns the file names.
             * 
             * @param directory Path of the directory to read.
             * @return std::vector<std::string> List of file names.
             */
            std::vector<std::string> readDirectory(std::string directory) const;
            std::vector<void *> _handles; ///< Handles to the dynamically loaded libraries.
            std::vector<std::shared_ptr<IGraphicLibrary>> _libraries; ///< Loaded graphic libraries.
            std::vector<std::shared_ptr<IGameLibrary>> _games; ///< Loaded game libraries.
            std::vector<arc::MenuComponent> _menus; ///< Menu components used in the interface.
            std::string username; ///< Username of the current player.
            arc::ArcadeState _state; ///< Current state of the arcade (e.g., menu, game).
            MenuManager *_menuManager; ///< Manager for handling menu logic.
            ToggleLibManager *_toggleLibManager; ///< Manager for handling library toggling.
            arc::IGraphicLibrary *_graphicLibrary; ///< Pointer to the current graphic library in use.
            void toggleLib(); ///< Toggles between different graphic libraries.
            int getCurrentLibraryIndex(); ///< Gets the index of the current graphic library in the list of loaded libraries.
            void loadLibrary(std::string lib); ///< Loads a specific graphic library.
            std::string helpMessage() const; ///< Returns a help message for command-line usage.
            void loadLibraries(); ///< Loads all graphic libraries.
            void loadGames(); ///< Loads all game libraries.
            ScoreboardManager *_scoreboardManager; ///< Manages the scoreboard for the games.
    };
}

#endif
