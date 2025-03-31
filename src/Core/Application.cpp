#include "Core/Application.hpp"
#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/ApplicationError.hpp"
#include "Core/DLLoader.hpp"
#include "Core/ArcadeState.hpp"
#include "Core/MenuManager.hpp"

arc::Application::Application(int ac, char **av)
{
    if (ac != 2) {
        throw ApplicationError("Usage: ./arcade lib/arcade_ncurses.so");
    }
    getGames();
    getLibraries();
    std::string lib = std::string(av[1]);
    username = "Martin";
    this->_menuManager = new arc::MenuManager(this->_libraries, this->_games, username);
    this->run(lib);
}

void arc::Application::getGames()
{

}

void arc::Application::getLibraries()
{
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

    try {
        libraries->Initialize();
        libraries->Open();
    } catch (const std::exception &e) {
        throw ApplicationError(e.what());
    }
    arc::DLLoader<arc::IGameLibrary> gameLoader("lib/arcade_snake.so");
    auto createGame = reinterpret_cast<arc::IGameLibrary *(*)()>(
        gameLoader.getFunction(gameLoader.getHandle(), "entryPoint")
    );
    arc::IGameLibrary *game = createGame();
    while (libraries->IsOpen()) {
        libraries->Clear();
        if (_menuManager->getState() == ArcadeState::LIB_MENU ||
            _menuManager->getState() == ArcadeState::GAME_MENU ||
            _menuManager->getState() == ArcadeState::CHANGE_USERNAME) {
            libraries->DrawMenu(_menuManager->getCurrentMenu());
        }
        if (_menuManager->getState() == ArcadeState::IN_GAME) {
            game->InitGame();
            _menuManager->_gameManager.LoadGame(_menuManager->getUsername(), game);
            libraries->DrawMap(_menuManager->getCurrentMap());
            libraries->DrawScore(_menuManager->getCurrentScore());
            // a retirer
        }
        event = libraries->HandleEvent();
        if (!_menuManager->processEvent(event, libraries->GetKeyPressed())) {
            libraries->Close();
            break;
        }
        libraries->Display();
    }
    libraries->Close();
    delete libraries;
}
