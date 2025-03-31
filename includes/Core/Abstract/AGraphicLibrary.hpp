/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** AGameLibrary.hpp
*/


#ifndef AGAMELIBRARY_HPP
# define AGAMELIBRARY_HPP

#include "Interface/IGraphicLibrary.hpp"
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include "Core/Click.hpp"
#include <map>
#include <any>

namespace arc::display {
    class AGraphicLibrary : virtual public IGraphicLibrary {
        public:
            virtual ~AGraphicLibrary() = default;
            virtual void Initialize() = 0;
            virtual void Open() = 0;
            virtual void Close() = 0;
            virtual bool IsOpen() = 0;
            virtual void Display() = 0;
            virtual void Clear() = 0;
            virtual void DrawComponent(const arc::RenderComponent& component) = 0;
            virtual void DrawComponents(const std::vector<arc::RenderComponent>& components) = 0;
            virtual void DrawMap(const std::vector<std::vector<arc::RenderComponent>>& map) = 0;
            virtual void DrawMenu(const arc::MenuComponent& map) = 0;
            virtual void DrawText(const arc::TextComponent& text) = 0;
            virtual void DrawScore(const int& score) = 0;
            virtual std::pair<int, int> GetMousePos() const = 0;
            virtual click GetMouseState() const = 0;
            virtual Event HandleEvent() = 0;
            virtual char GetKeyPressed() = 0;
            virtual void LoadResources(std::string filepath, arc::type type) = 0;
            virtual void UnloadResources(std::string filepath, arc::type type) = 0;
            virtual void LaunchMusic(std::string filepath) = 0;
            virtual void StopMusic(std::string filepath) = 0;
            virtual std::string GetName() const = 0;

        protected:
            std::string _name;
            std::map<std::string, std::any> _assets;
    };
}

#endif