
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
#include <ncurses.h>
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include "Core/Click.hpp"
#include "Core/Components/IObject.hpp"
#include <vector>
#include <map>
#include <any>

namespace arc::display {
    class Ncurses : public AGraphicLibrary {
        public:
            Ncurses();
            ~Ncurses();
            void Initialize() override;
            void Open() override;
            void Close() override;
            bool IsOpen() override;
            void Display() override;
            void Clear() override;
            void DrawComponent(const arc::RenderComponent& component) override;
            void DrawComponents(const std::vector<arc::RenderComponent>& components) override;
            void DrawMap(const std::vector<std::vector<arc::RenderComponent>>& map) override;
            void DrawText(const arc::TextComponent& text) override;
            void DrawMenu(const arc::MenuComponent& menu) override;
            void DrawScore(const int& score) override;
            std::pair<int, int> GetMousePos() const override;
            click GetMouseState() const override;
            Event HandleEvent() override;
            std::string GetName() const override;
            char GetKeyPressed() override;
            void LoadResources(std::string filepath, arc::type type) override;
            void UnloadResources(std::string filepath, arc::type type) override;
            void LaunchMusic(std::string filepath) override;
            void StopMusic(std::string filepath) override;
        protected:
            std::string _name = "Ncurses";
            std::map<std::string, std::vector<arc::IObject>> _objects;
            std::map<std::string, std::any> _assets;
            int middle;
            char key;
        private:
    };
}

extern "C" void *entryPoint();
#endif