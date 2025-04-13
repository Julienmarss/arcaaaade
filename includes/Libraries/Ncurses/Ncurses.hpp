/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Ncurses.hpp
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "Core/Abstract/AGraphicLibrary.hpp"
#include "Interface/IGraphicLibrary.hpp"
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include "Core/Click.hpp"
#include <vector>
#include <map>
#include <any>
#include <ncurses.h>

namespace arc::display {

    /**
     * @class Ncurses
     * @brief Implementation of AGraphicLibrary using the Ncurses text-based UI.
     * 
     * This backend allows the game to run in a terminal with character-based rendering.
     */
    class Ncurses : public AGraphicLibrary {
    public:
        /**
         * @brief Constructs the Ncurses graphical backend.
         */
        Ncurses();

        /**
         * @brief Destructor that ensures cleanup of Ncurses ressources.
         */
        ~Ncurses();

        void Initialize() override;
        void Open() override;
        void Close() override;
        bool IsOpen() override;
        void Display() override;
        void Clear() override;

        void DrawComponent(std::shared_ptr<arc::RenderComponent> component) override;
        void DrawComponents(std::vector<std::shared_ptr<arc::RenderComponent>> components) override;
        void DrawMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map) override;
        void DrawText(std::shared_ptr<arc::TextComponent> text) override;
        void DrawMenu(std::shared_ptr<arc::MenuComponent> menu) override;
        void DrawScore(const int& score, std::shared_ptr<arc::TextComponent> text) override;

        std::pair<int, int> GetMousePos() const override;
        click GetMouseState() const override;
        Event HandleEvent() override;
        char GetKeyPressed() override;

        void LoadResources(std::string filepath, type type) override;
        void UnloadResources(std::string filepath, type type) override;
        void LaunchMusic(std::string filepath) override;
        void StopMusic(std::string filepath) override;

        /**
         * @brief Returns the name of the library.
         * 
         * @return The name "Ncurses".
         */
        std::string GetName() const override;

    protected:
        std::string _name = "Ncurses"; ///< Name of the library
        std::map<std::string, std::any> _assets; ///< Assets map (not used in Ncurses but kept for consistency)
        int middle; ///< Center position for UI alignment
        char key;   ///< Last key pressed
    };

}

/**
 * @brief Entry point for dynamic loading.
 * 
 * @return Pointer to the Ncurses instance.
 */
extern "C" void *entryPoint();

#endif // NCURSES_HPP_
