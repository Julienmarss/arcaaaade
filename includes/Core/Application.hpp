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
#include "Interface/ILibraryModule.hpp"
#include "Interface/IGameModule.hpp"

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
            std::vector<std::string> readDirectory(std::string directory) const;
            std::vector<void *> _handles;
            std::vector<std::shared_ptr<ILibraryModule>> _libraries;
            std::vector<std::shared_ptr<IGameModule>> _games;
            std::shared_ptr<ILibraryModule> _currentLibrary;
            std::shared_ptr<IGameModule> _currentGame;
            std::string username;
    };
}

#endif