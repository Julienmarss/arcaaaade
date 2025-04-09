/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuManager.hpp
*/

#ifndef MENUMANAGER_HPP
# define MENUMANAGER_HPP

#include <vector>
#include <string>
#include <memory>
#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "ApplicationError.hpp"
#include "Core/ArcadeState.hpp"
#include "Core/GameManager.hpp"

namespace arc {

    /**
     * @class MenuManager
     * @brief Manages menus, user input, and game selection for the arcade.
     */
    class MenuManager {
    public:
        /**
         * @brief Constructs the MenuManager with libraries, games, and a username.
         * 
         * @param _libraries Available graphic libraries.
         * @param _games Available game libraries.
         * @param username Player's username.
         */
        MenuManager(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games, std::string username);

        /**
         * @brief Destructor for MenuManager.
         */
        ~MenuManager();

        /**
         * @brief Loads and sets up the menus.
         * 
         * @param _libraries List of graphic libraries.
         * @param _games List of game libraries.
         */
        void loadMenus(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games);

        /**
         * @brief Processes a user input event.
         * 
         * @param event The event to process.
         * @param key The character key that was pressed.
         * @return True if the event was handled, false otherwise.
         */
        bool processEvent(Event event, char key);

        /**
         * @brief Gets the currently active menu.
         * 
         * @return The current MenuComponent.
         */
        const MenuComponent& getCurrentMenu() const;

        /**
         * @brief Gets the current application state.
         * 
         * @return The current ArcadeState.
         */
        arc::ArcadeState getState() const;

        /**
         * @brief Sets the current application state.
         * 
         * @param newState The new ArcadeState.
         */
        void setState(arc::ArcadeState newState);

        /**
         * @brief Sets the username.
         * 
         * @param username The new username.
         */
        void setUsername(const std::string &username);

        /**
         * @brief Gets the current username.
         * 
         * @return The username string.
         */
        const std::string& getUsername() const;

        /**
         * @brief Gets the current on-screen text.
         * 
         * @return A TextComponent containing the text.
         */
        const arc::TextComponent getCurrentText() const;

        /**
         * @brief Gets the currently selected game.
         * 
         * @return A pointer to the current IGameLibrary.
         */
        const IGameLibrary* getCurrentGame() const;

        /**
         * @brief Gets the currently selected game (non-const).
         * 
         * @return A pointer to the current IGameLibrary.
         */
        IGameLibrary* getCurrentGame();

        std::vector<MenuComponent> _menus;          ///< List of menu components.
        arc::GameManager _gameManager;              ///< Manages the game session.

    private:
        arc::ArcadeState _state;                    ///< Current state of the arcade (e.g., menu, playing).
        std::vector<std::shared_ptr<IGraphicLibrary>> _libraries; ///< Available graphic libraries.
        std::vector<std::shared_ptr<IGameLibrary>> _games;        ///< Available game libraries.
        IGameLibrary *_game;                        ///< Currently selected game.
        std::string _username;                      ///< Username of the current player.

        /**
         * @brief Replaces the title of the current menu.
         * 
         * @param title New title to set.
         */
        void replaceCurrentTitleMenu(const std::string &title);

        /**
         * @brief Updates the displayed username in the menu.
         * 
         * @param username The new username.
         */
        void updateUsername(const std::string &username);

        /**
         * @brief Checks if the pressed key is valid in the context of the menu.
         * 
         * @param key The key pressed.
         * @return True if valid, false otherwise.
         */
        bool isValidKey(char key) const;
    };

}

#endif // MENUMANAGER_HPP
