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
#include <memory>

namespace arc {
    class Application
    {
        public:
            Application(int ac, char **av);
            ~Application();
            void run(std::string lib);
        private:
            void getLibraries();
            void getGames();
            void loadMenus();
            std::vector<std::string> readDirectory(std::string directory) const;
            std::vector<void *> _handles;
            std::vector<std::shared_ptr<IGraphicLibrary>> _libraries;
            std::vector<std::shared_ptr<IGameLibrary>> _games;
            std::vector<arc::MenuComponent> _menus;
            std::shared_ptr<IGraphicLibrary> _currentLibrary;
            std::shared_ptr<IGameLibrary> _currentGame;
            std::string username;
            arc::ArcadeState _state;
            MenuManager *_menuManager;
    };
}

#endif