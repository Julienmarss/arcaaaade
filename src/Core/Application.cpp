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
    if (ac != 2) {
        throw ApplicationError("Usage: ./arcade lib/arcade_ncurses.so");
    }
    getGames();
    getLibraries();
    std::cout << "Bibliothèques chargées: " << _libraries.size() << std::endl;
    for (const auto& lib : _libraries) {
        std::cout << " - " << lib->GetName() << std::endl;
    }
    
    std::cout << "Jeux chargés: " << _games.size() << std::endl;
    for (const auto& game : _games) {
        std::cout << " - " << game->GetName() << std::endl;
    }
    std::string lib = std::string(av[1]);
    username = "Martin";
    this->_menuManager = new arc::MenuManager(_libraries, _games, username);
    this->run(lib);
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
        std::cerr << "Impossible d'ouvrir le répertoire " << directory << std::endl;
    }
    return files;
}

void arc::Application::getLibraries()
{
    std::vector<std::string> files = readDirectory("./lib");
    
    for (const auto& file : files) {
        try {
            if (file.find("arcade_") != std::string::npos && 
                file.find("snake") == std::string::npos && 
                file.find("nibbler") == std::string::npos) {
                
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
                
                std::cout << "Library loaded: " << file << " - " << graphicLib->GetName() << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error in graphic library loading: " << file << ": " << e.what() << std::endl;
        }
    }
}

void arc::Application::getGames()
{
    std::vector<std::string> files = readDirectory("./lib");
    
    for (const auto& file : files) {
        try {
            if (file.find("snake") != std::string::npos || 
                file.find("nibbler") != std::string::npos) {
                
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
                
                std::cout << "Game loaded: " << file << " - " << gameLib->GetName() << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error in game loading: " << file << ": " << e.what() << std::endl;
        }
    }
}

arc::Application::~Application()
{
    delete this->_menuManager;
}

void arc::Application::run(std::string lib)
{
    arc::DLLoader<arc::IGraphicLibrary> loader(lib);

    if (loader.isGraphical() == false) {
        throw ApplicationError("Error: the library is not graphical");
    }
    auto createLibraries = reinterpret_cast<arc::IGraphicLibrary *(*)()>(
        loader.getFunction(loader.getHandle(), "entryPoint")
    );
    arc::IGraphicLibrary *libraries = createLibraries();
    Event event = Event::TEXT_INPUT;
    Event lastEvent = Event::TEXT_INPUT; 
    int score = 0;
    std::vector<std::vector<arc::RenderComponent>> map;
    std::chrono::steady_clock::time_point lastUpdate = std::chrono::steady_clock::now();
    std::chrono::milliseconds updateInterval(1000);
    
    try {
        libraries->Initialize();
        libraries->Open();
    } catch (const std::exception &e) {
        throw ApplicationError(e.what());
    }
    while (libraries->IsOpen()) {
        libraries->Clear();
        if (_menuManager->getState() == ArcadeState::LIB_MENU ||
            _menuManager->getState() == ArcadeState::GAME_MENU ||
            _menuManager->getState() == ArcadeState::CHANGE_USERNAME) {
            libraries->DrawMenu(_menuManager->getCurrentMenu());
        }
        event = libraries->HandleEvent();
        char currentKey = libraries->GetKeyPressed();
        if (_menuManager->getState() == ArcadeState::IN_GAME) {
            auto currentTime = std::chrono::steady_clock::now();
            if (currentTime - lastUpdate >= updateInterval) {
                _menuManager->getCurrentGame()->Update(libraries->GetMouseState(), lastEvent);
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
            libraries->DrawMap(map);
            libraries->DrawScore(score, _menuManager->getCurrentText());
            
            if (_menuManager->getCurrentGame()->IsGameOver()) {
                _menuManager->setState(ArcadeState::GAME_MENU);
                _menuManager->getCurrentGame()->Reset();
                _menuManager->getCurrentGame()->CloseGame();
            }
    
        }
        if (!_menuManager->processEvent(event, currentKey)) {
            libraries->Close();
            break;
        }
        libraries->Display();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    libraries->Close();
    delete libraries;
}
