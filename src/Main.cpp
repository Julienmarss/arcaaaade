/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** main.cpp
*/
#include <iostream>
#include <stdexcept>
#include "Core/Application.hpp"

int main(int ac, char **av)
{
    try {
        arc::Application app(ac, av);

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
