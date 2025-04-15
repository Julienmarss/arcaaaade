#include "Core/Application.hpp"
#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/ApplicationError.hpp"
#include "Core/DLLoader.hpp"
#include "Core/ArcadeState.hpp"
#include "Core/MenuManager.hpp"
#include <dirent.h>
#include <dlfcn.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <chrono>
#include <thread>
arc::Application::Application(int ac, char **av)
{
    getGames();
    getLibraries();
    if (ac != 2) {
        throw ApplicationError(helpMessage());
    }
    std::cout << "Lib loadded: " << _libraries.size() << std::endl;
    for (const auto& lib : _libraries) {
        std::cout << " - " << lib->GetName() << std::endl;
    }
    
    std::cout << "Games loadded: " << _games.size() << std::endl;
    for (const auto& game : _games) {
        std::cout << " - " << game->GetName() << std::endl;
    }
    std::string lib = std::string(av[1]);
    username = "Martin";
    this->loadLibrary(lib);
    this->loadLibraries();
    this->loadGames();
    this->_scoreboardManager = new arc::ScoreboardManager();
    this->_scoreboardManager->loadScoresFromFile("./scores.txt");
    this->_toggleLibManager = new arc::ToggleLibManager(_libraries);
    this->_menuManager = new arc::MenuManager(_libraries, _games, username, this->getCurrentLibraryIndex(), this->_scoreboardManager, this->_toggleLibManager);
    this->run();
}

arc::Application::~Application()
{
}

void arc::Application::loadLibraries()
{
    for (const auto& lib : _libraries) {
        try {
            lib->Initialize();
            std::cout << "Library loaded: " << lib->GetName() << std::endl;
        } catch (const std::exception &e) {
            throw ApplicationError(e.what());
        }
    }
}

void arc::Application::loadGames()
{
    for (const auto& game : _games) {
        try {
            std::cout << "Game loaded: " << game->GetName() << std::endl;
        } catch (const std::exception &e) {
            throw ApplicationError(e.what());
        }
    }
}

std::string arc::Application::helpMessage() const
{
    std::string libraryNames;
    std::string gameNames;
    for (const auto& lib : _libraries) {
        libraryNames += lib->GetName() + " ";
    }
    for (const auto& game : _games) {
        gameNames += game->GetName() + " ";
    }
    libraryNames += "\n";
    gameNames += "\n";

    return "Usage: ./arcade <lib_name>\n"
           "Available libraries: " + libraryNames + "\n"
           "Available games: " + gameNames + "\n"
           "Keyboard controls: \n"
           " - Arrow keys: Move the cursor\n"
           " - Enter: Select a menu item\n"
           " - Escape: Exit the game\n"
           " - Backspace: Go back to the previous menu\n"
           " - Q - Previous library\n"
           " - D - Next library\n"
           " - H - Previous game\n"
           " - L - Next game\n"
           " - R - Restart the game\n";
}

std::vector<std::string> arc::Application::readDirectory(std::string directory) const
{
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    
    dir = opendir(directory.c_str());
    if (dir != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if (ent->d_name[0] != '.') {
                std::string filename = ent->d_name;
                if (filename.size() > 3 && 
                    filename.substr(filename.size() - 3) == ".so") {
                    files.push_back(directory + "/" + filename);
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Cannot read directory " << directory << std::endl;
    }
    return files;
}

void arc::Application::getLibraries()
{

    const std::vector<std::string> validLibNames = {
        "ncurses", "sdl2", "ndk++", "libcaca", "allegro5", "xlib", 
        "gtk+", "sfml", "irrlicht", "opengl", "vulkan", "qt5"
    };
    std::vector<std::string> files = readDirectory("./lib");
    
    for (const auto& file : files) {
        try {
            bool isValidLib = false;
                for (const auto& validLib : validLibNames) {
                    if (file.find(validLib) != std::string::npos) {
                        isValidLib = true;
                        break;
                    }
                }
                if (!isValidLib) {
                    continue;
                }
                
                void* handle = dlopen(file.c_str(), RTLD_NOW | RTLD_GLOBAL);
                if (!handle) {
                    std::cerr << "Error in graphic library loading: " << file << ": " << dlerror() << std::endl;
                    continue;
                }
                _handles.push_back(handle);
                
                void* entryPointSymbol = dlsym(handle, "entryPoint");
                if (!entryPointSymbol) {
                    std::cerr << "Error: entryPoint function not found in " << file << std::endl;
                    continue;
                }
                
                auto entryPoint = reinterpret_cast<void *(*)()>(entryPointSymbol);
                
                void* instance = entryPoint();
                arc::IGraphicLibrary* graphicLib = static_cast<arc::IGraphicLibrary*>(instance);
                
                _libraries.push_back(std::shared_ptr<IGraphicLibrary>(graphicLib));
                
        } catch (const std::exception& e) {
            std::cerr << "Error in graphic library loading: " << file << ": " << e.what() << std::endl;
        }
    }
}

void arc::Application::getGames()
{
    std::vector<std::string> files = readDirectory("./lib");

    const std::vector<std::string> validGameNames = {
        "snake", "minesweeper", "nibbler", "pacman", 
        "qix", "centipede", "solarfox"
    };
    
    for (const auto& file : files) {
        try {
            bool isValidGame = false;
            for (const auto& validGame : validGameNames) {
                if (file.find(validGame) != std::string::npos) {
                    isValidGame = true;
                    break;
                }
            }
            
            if (!isValidGame) {
                continue;
            }
            void* handle = dlopen(file.c_str(), RTLD_NOW | RTLD_GLOBAL);
            if (!handle) {
                std::cerr << "Error in game loading: " << file << ": " << dlerror() << std::endl;
                continue;
            }
            _handles.push_back(handle);
            
            void* entryPointSymbol = dlsym(handle, "entryPoint");
            if (!entryPointSymbol) {
                std::cerr << "Error: entryPoint not found " << file << std::endl;
                continue;
            }
            
            auto entryPoint = reinterpret_cast<void *(*)()>(entryPointSymbol);
            
            void* instance = entryPoint();
            arc::IGameLibrary* gameLib = static_cast<arc::IGameLibrary*>(instance);
            _games.push_back(std::shared_ptr<IGameLibrary>(gameLib));
        } catch (const std::exception& e) {
            std::cerr << "Error in game loading: " << file << ": " << e.what() << std::endl;
        }
    }
}

void arc::Application::loadLibrary(std::string lib)
 {
    arc::DLLoader<arc::IGraphicLibrary> loader(lib);

    if (loader.isGraphical() == false) {
        throw ApplicationError("Error: the library is not graphical");
    }
    auto createLibraries = reinterpret_cast<arc::IGraphicLibrary *(*)()>(
        loader.getFunction(loader.getHandle(), "entryPoint")
    );
    arc::IGraphicLibrary *libraries = createLibraries();
    this->_graphicLibrary = libraries;
 }
 
void arc::Application::run()
{
    Event event = Event::TEXT_INPUT;
    Event lastEvent = Event::TEXT_INPUT; 
    int score = 0;
    std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map;
    std::chrono::steady_clock::time_point lastUpdate = std::chrono::steady_clock::now();
    std::chrono::milliseconds updateInterval(500);
    
    try {
        _graphicLibrary->Initialize();
        _graphicLibrary->Open();
    } catch (const std::exception &e) {
        throw ApplicationError(e.what());
    }
    _toggleLibManager->setCurrentLib(this->getCurrentLibraryIndex());
    while (_graphicLibrary->IsOpen()) {
        _graphicLibrary->Clear();
        if (_menuManager->getState() == ArcadeState::LIB_MENU ||
            _menuManager->getState() == ArcadeState::GAME_MENU ||
            _menuManager->getState() == ArcadeState::GAME_OVER || 
            _menuManager->getState() == ArcadeState::CHANGE_USERNAME) {
            _graphicLibrary->DrawMenu(_menuManager->getCurrentMenu());
        }
        if (_menuManager->getState() == ArcadeState::CHANGE_USERNAME) {
            this->_scoreboardManager->printScores(_menuManager->_menus[1]->GetSelectedItem()->GetText(), _graphicLibrary);
        }
        event = _graphicLibrary->HandleEvent();
        char currentKey = _graphicLibrary->GetKeyPressed();
        if (_menuManager->getState() == ArcadeState::IN_GAME) {
            auto currentTime = std::chrono::steady_clock::now();
            if (currentTime - lastUpdate >= updateInterval) {
                _menuManager->getCurrentGame()->Update(_graphicLibrary->GetMouseState(), lastEvent);
                lastUpdate = currentTime;
                lastEvent = Event::TEXT_INPUT;
            }
            if (event != Event::TEXT_INPUT) {
                //_menuManager->getCurrentGame()->Update(libraries->GetMouseState(), lastEvent);
                //lastUpdate = currentTime;
                lastEvent = event;
            }
            score = _menuManager->getCurrentGame()->GetScore();
            map = _menuManager->getCurrentGame()->GetMap();
            _graphicLibrary->DrawMap(map);
            _graphicLibrary->DrawScore(score, _menuManager->getCurrentText());
            
            if (_menuManager->getCurrentGame()->IsGameOver()) {
                std::cout << "Game Over" << std::endl;
                std::cout << "Score: " << score << std::endl;
                _menuManager->setState(ArcadeState::GAME_OVER);
                _menuManager->getCurrentGame()->Reset();
            }
    
        }
        if (!_menuManager->processEvent(event, currentKey)) {
            _graphicLibrary->Close();
            break;
        }
        if (_toggleLibManager->isToggleEvent(event)) {
            toggleLib();
            continue;
        }
        _graphicLibrary->Display();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    _graphicLibrary->Close();
    delete _graphicLibrary;
}

void arc::Application::toggleLib()
{
    auto nextLib = _toggleLibManager->getNextLib();
    _graphicLibrary->Close();
    _graphicLibrary = nextLib.get();
    _graphicLibrary->Initialize();
    _graphicLibrary->Open();
}

int arc::Application::getCurrentLibraryIndex()
{
    for (size_t i = 0; i < _libraries.size(); ++i) {
        if (_libraries[i]->GetName() == _graphicLibrary->GetName()) {
            return i;
        }
    }
    return -1;
}