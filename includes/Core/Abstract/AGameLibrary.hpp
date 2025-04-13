/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** AGameLibrary.hpp
*/
#ifndef AGRAPHICALLIBRARY_HPP
#define AGRAPHICALLIBRARY_HPP
#include "Interface/IGameLibrary.hpp"
#include <string>
#include <vector>
#include "Core/Click.hpp"
#include "Core/Event.hpp"
#include "Core/Components/RenderComponent.hpp"
#include <map>
#include <any>
#include <memory>

namespace arc::games {
    class AGameLibrary : virtual public IGameLibrary {
        public:
            AGameLibrary() = default;
			virtual bool Update(click state, Event key) = 0;
            virtual void AddObject(std::string name, std::shared_ptr<arc::RenderComponent>) = 0;
            virtual void DeleteObject(std::string name) = 0;
            virtual std::vector<std::shared_ptr<arc::RenderComponent>> GetObjects(std::string name) const = 0;
            virtual int GetScore() const = 0;
            virtual bool IsGameOver() const = 0;
            virtual void Reset() = 0;
            virtual std::string GetName() const = 0;
            virtual void InitGame() = 0;
            virtual void CloseGame() = 0;
            virtual void AddMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>>) = 0;
            virtual std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> GetMap() const = 0;
        protected:
            unsigned int _score = 0;
            std::string _gameName;
            bool _gameOver = false;
            std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> _map;
            std::map<std::string, std::vector<std::shared_ptr<arc::RenderComponent>>> _objects;
        private:
    };
}
#endif