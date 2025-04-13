#ifndef NCURSESWRAPPER_HPP
# define NCURSESWRAPPER_HPP

#include <ncurses.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <cstring>
namespace arc {
    class NcursesWrapper {
        public:
            static void init();
            static void end();
            static void clear();
            static void refresh();
            static void print(int x, int y, const std::string &str, const std::string &format = "");
            static void printChar(int x, int y, char c);
            static int getChar();
            static void setAttr(int attr);
            static void unsetAttr(int attr);
            static void initColor(int pair, int fg, int bg);
            static void setupWindow();
            static int getMaxX();
            static int getMaxY();
    };
    class NcursesWrapperException : public std::exception {
        public:
            NcursesWrapperException(const std::string &message) : _message(message) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };
}

#endif