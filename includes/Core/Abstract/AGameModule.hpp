/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** AGameModule.hpp
*/
#ifndef AGAMEMODULE_HPP
#define AGAMEMODULE_HPP
#include "Interface/IGameModule.hpp"

namespace arc::games {
    class AGameModule : virtual public IGameModule {
        public:
            AGameModule() = default;
            virtual void initGame() = 0;
            virtual void updateGame() = 0;
            virtual void displayGame() = 0;
            virtual void closeGame() = 0;
            virtual ~AGameModule() = default;
        protected:
        private:
    };
}
#endif