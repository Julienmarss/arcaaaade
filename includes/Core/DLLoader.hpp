/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** DLLoader.hpp
*/

#ifndef DLLOADER_HPP
# define DLLOADER_HPP
#include <iostream>
#include <stdexcept>
#include <string>
namespace arc {
    template<typename T>
    class DLLoader
    {
        public:
            DLLoader(const std::string &path);
            ~DLLoader();
            void *getFunction(void *handle, std::string functionName) const;
            void *getHandle() const;
            bool isGraphical() const;
        private:
            std::string libPath;
            void* _handle;
            std::string getDlError() const;
    
    };
}    
#endif