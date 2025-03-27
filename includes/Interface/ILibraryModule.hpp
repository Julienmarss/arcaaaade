/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ILibraryModule.hpp
*/

#ifndef ILIBRARYMODULE_HPP
# define ILIBRARYMODULE_HPP

#include <iostream>
#include <string>
namespace arc {
    class ILibraryModule {
        public:
            virtual ~ILibraryModule() = default;
            virtual void init() = 0;
            virtual void stop() = 0;
            virtual const std::string &getName() const = 0;
    };
}

#endif