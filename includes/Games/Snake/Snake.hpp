/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Snake.hpp
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "Core/Abstract/AGameLibrary.hpp"
#include "Core/Click.hpp"
#include "Core/Event.hpp"
namespace arc::games {
    class Snake : public AGameLibrary {
        public:
            Snake();
            ~Snake();
            bool Update(click state, Event key);
            void AddObject(std::string name, arc::RenderComponent);
            void DeleteObject(std::string name);
            std::vector<arc::RenderComponent> GetObjects(std::string name) const;
            int GetScore() const;
            bool IsGameOver() const;
            void Reset();
            std::string GetName() const;
            void InitGame();
            void CloseGame();
        protected:
        private:
            std::map<std::string, std::vector<arc::RenderComponent>> _objects;
    };
}
extern "C" void *entryPoint();
#endif