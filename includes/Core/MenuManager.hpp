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
#include "Interface/IGraphicLibrary.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "ApplicationError.hpp"
#include <memory>
#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/ArcadeState.hpp"
#include "Core/GameManager.hpp"

namespace arc {
    class MenuManager {
    public:
        MenuManager(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games, std::string username);
        ~MenuManager();
        void loadMenus(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games);
        bool processEvent(Event event, char key);
        const MenuComponent& getCurrentMenu() const;
        arc::ArcadeState getState() const;
        void setState(arc::ArcadeState newState);
        void setUsername(const std::string &username);
        const std::string& getUsername() const;
        const std::vector<std::vector<arc::RenderComponent>> getCurrentMap() const;
        int getCurrentScore() const;
        std::vector<MenuComponent> _menus;
        arc::GameManager _gameManager;
    private:
        arc::ArcadeState _state;
        std::vector<std::shared_ptr<IGraphicLibrary>> _libraries;
        std::vector<std::shared_ptr<IGameLibrary>> _games;
        std::string _username;
        void replaceCurrentTitleMenu(const std::string &title);
        void updateUsername(const std::string &username);
        bool isValidKey(char key) const;
    };

}

#endif
