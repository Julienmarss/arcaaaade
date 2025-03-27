/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Ncurses.cpp
*/

#include "Libraries/Ncurses/Ncurses.hpp"
#include "Interface/ILibraryModule.hpp"
#include <ncurses.h>


extern "C" arc::ILibraryModule *createLibraries()
{
    return new arc::libraries::Ncurses;
}

extern "C" void destroyLibraries(arc::ILibraryModule *libraries)
{
    delete dynamic_cast<arc::libraries::Ncurses *>(libraries);
}


arc::libraries::Ncurses::Ncurses()
{
}

arc::libraries::Ncurses::~Ncurses()
{
}
void arc::libraries::Ncurses::init()
{
    std::cout << "Ncurses init" << std::endl;
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    while (1) {
        int ch = getch();
        if (ch == 'q') // Exit loop on 'q' key press
            break;

        // Example: Display a message in the center of the screen
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(LINES / 2, (COLS - 20) / 2, "Press 'q' to quit.");
        attroff(COLOR_PAIR(1));
        refresh();
    }
}

void arc::libraries::Ncurses::stop()
{
    std::cout << "Ncurses stop" << std::endl;
    endwin();
}

const std::string &arc::libraries::Ncurses::getName() const
{
    static const std::string name = "Ncurses";
    return name;
}