/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Application.cpp
*/

#include "Core/Application.hpp"
#include "Interface/ILibraryModule.hpp"
#include "Interface/IGameModule.hpp"
#include "Core/ApplicationError.hpp"
#include "Core/DLLoader.hpp"

arc::Application::Application(int ac, char **av)
{
    if (ac != 2) {
        throw ApplicationError("Usage: ./arcade lib/arcade_ncurses.so");
    }
    getGames();
    getLibraries();
    if (_libraries.empty() == true) {
        throw ApplicationError("Error: no libraries found");
    }
    std::string lib = std::string(av[1]);
    if (_games.empty() == true) {
        throw ApplicationError("Error: no games found");
    }
    username = "Martin";
    this->run(lib);
}

arc::Application::~Application()
{
}

void arc::Application::getGames()
{
    // Note : faire en sorte de lire le contenu du dossier games et de récupérer les jeux (en vérifiant avec le DDLLoader->isGraphical())
    // et les stocker dans le vector _games
}

void arc::Application::getLibraries()
{
    // Note : faire en sorte de lire le contenu du dossier lib et de récupérer les librairies (en vérifiant avec le DDLLoader->isGraphical())
    // et les stocker dans le vector _libraries
}

std::vector<std::string> arc::Application::readDirectory(std::string directory) const
{
    (void) directory;
    // Note : faire en sorte de lire le contenu du dossier demandé et de retourner un vector de string contenant les noms des fichiers
    return std::vector<std::string>();
}

void arc::Application::run(std::string lib)
{
    arc::DLLoader<arc::ILibraryModule> loader(lib);

    if (loader.isGraphical() == false) {
        throw ApplicationError("Error: the library is not graphical");
    }
    auto createLibraries = reinterpret_cast<arc::ILibraryModule *(*)()>(loader.getFunction(loader.getHandle(), "createLibraries"));
    arc::ILibraryModule *libraries = createLibraries();
    libraries->init();
    std::cout << libraries->getName() << std::endl;
    libraries->stop();
    delete libraries;
}
