/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** NcursesWrapper.cpp
*/

#include "Libraries/Ncurses/NcursesWrapper.hpp"

#include <ncurses.h>
#include <string.h>

void arc::NcursesWrapper::init()
{
    if (!initscr()) {
        throw NcursesWrapperException("Failed to initialize ncurses");
    }
}

void arc::NcursesWrapper::end()
{
    endwin();
}

void arc::NcursesWrapper::clear()
{
    if (::clear() == ERR) {
        throw NcursesWrapperException("Failed to clear screen");
    }
}

void arc::NcursesWrapper::refresh()
{
    if (::refresh() == ERR) {
        throw NcursesWrapperException("Failed to refresh screen");
    }
}

void arc::NcursesWrapper::print(int x, int y, const std::string &str, const std::string &format)
{
    if (x < 0 || y < 0) {
        throw NcursesWrapperException("Invalid coordinates");
    }
    if (x >= getMaxX()) {
        x = getMaxX() - 10;
    }
    if (y >= getMaxY()) {
        y = getMaxY() - 10;
    }

    if (mvprintw(y, x, str.c_str(), format.c_str()) == ERR) {
        throw NcursesWrapperException("Failed to print string");
    }
}

void arc::NcursesWrapper::printChar(int x, int y, char c)
{
    mvaddch(x, y, c);
}
void arc::NcursesWrapper::setAttr(int attr)
{
    if (attron(COLOR_PAIR(attr)) == ERR) {
        throw NcursesWrapperException("Failed to set attribute");
    }
}

void arc::NcursesWrapper::unsetAttr(int attr)
{
    if (attroff(COLOR_PAIR(attr)) == ERR) {
        throw NcursesWrapperException("Failed to unset attribute");
    }
}

void arc::NcursesWrapper::initColor(int pair, int fg, int bg)
{
    if (init_pair(pair, fg, bg) == ERR) {
        throw NcursesWrapperException("Failed to initialize color pair");
    }
}

void arc::NcursesWrapper::setupWindow()
{
    nodelay(stdscr, TRUE);
    scroll(stdscr);
    scrollok(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

int arc::NcursesWrapper::getMaxX()
{
    return getmaxx(stdscr);
}

int arc::NcursesWrapper::getMaxY()
{
    return getmaxy(stdscr);
}

int arc::NcursesWrapper::getChar()
{
    return getch();
}