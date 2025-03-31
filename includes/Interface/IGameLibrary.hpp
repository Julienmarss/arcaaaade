/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** IGameLibrary.hpp
*/

#ifndef IGAMELIBRARY_HPP
# define IGAMELIBRARY_HPP

#include <string>
#include <vector>
#include <map>
#include "Core/Click.hpp"
#include "Core/Event.hpp"
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/IObject.hpp"

namespace arc {

    enum GameState {
    };

    class IGameLibrary {
    public:
        virtual ~IGameLibrary() = default;

        virtual bool Update(click state, Event key) = 0;

        virtual void AddObject(std::string name, RenderComponent) = 0;
        virtual void DeleteObject(std::string name) = 0;
        virtual std::vector<RenderComponent> GetObjects(std::string name) const = 0;

        virtual int GetScore() const = 0;

        virtual bool IsGameOver() const = 0;
        virtual void Reset() = 0;
        virtual std::string GetName() const = 0;

        virtual void InitGame() = 0;
        virtual void CloseGame() = 0;
    };
}

#endif