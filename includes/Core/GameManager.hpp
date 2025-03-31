#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP
# include <iostream>
# include <vector>

# include <string>
# include <map>
# include <memory>
# include "Core/Abstract/AGraphicLibrary.hpp"
# include "Core/Abstract/AGameLibrary.hpp"
#include "Core/MapManager.hpp"

namespace arc {
    class GameManager {
        public:
            GameManager();
            ~GameManager();
            void LoadGame(const std::string &username, IGameLibrary *game);
            void run();
            std::vector<std::vector<arc::RenderComponent>> getCurrentMap() const;
            int getCurrentScore() const;
            void displayMap();
        private:
            int _score;
            MapManager _mapManager;
            std::vector<std::vector<arc::RenderComponent>> _map;
    };
}

#endif