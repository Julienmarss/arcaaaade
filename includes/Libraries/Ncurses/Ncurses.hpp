
/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Ncurses.hpp
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "Core/Abstract/ALibraryModule.hpp"

namespace arc::libraries {
    class Ncurses : public ALibraryModule {
        public:
            Ncurses();
            ~Ncurses();
            void init() override;
            void stop() override;
            const std::string &getName() const override;
        protected:
        private:
    };
}

extern "C" arc::ILibraryModule *createDisplay();
extern "C" void destroyDisplay(arc::ILibraryModule *display);
#endif