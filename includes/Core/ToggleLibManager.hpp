/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ToggleLibManager.hpp
*/

#include <vector>
#include <memory>
#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/Event.hpp"
#include "Core/Click.hpp"

#ifndef TOGGLELIBMANAGER_HPP
# define TOGGLELIBMANAGER_HPP

namespace arc {
    class ToggleLibManager {
        public:
            ToggleLibManager(std::vector<std::shared_ptr<IGraphicLibrary>> libraries);
            ~ToggleLibManager();
            bool isToggleEvent(Event event);
            void setNextLib(int index);
            std::shared_ptr<IGraphicLibrary> getNextLib();
            void setCurrentLib(int index);
        private:
            std::vector<std::shared_ptr<IGraphicLibrary>> _libraries;
            std::shared_ptr<IGraphicLibrary> _nextGraphicLibrary;
            Event _event;
            bool isToggle;
    };
}

#endif