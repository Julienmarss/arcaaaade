/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Snake.hpp
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "Core/Abstract/AGameModule.hpp"
namespace arc::games {
    class Snake : public AGameModule {
        public:
            Snake();
            ~Snake();
            void initGame();
            void updateGame();
            void displayGame();
            void closeGame();
        protected:
        private:
    };
}
#endif