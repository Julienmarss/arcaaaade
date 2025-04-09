/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** DLLoader.cpp
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <dlfcn.h>

#include "Interface/IGraphicLibrary.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/DLLoader.hpp"

template class arc::DLLoader<arc::IGameLibrary>;

template<typename T>
arc::DLLoader<T>::DLLoader(const std::string &path) : libPath(path), _handle(nullptr)
{
    _handle = dlopen(libPath.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (_handle == nullptr) {
        throw std::runtime_error("Error in loading of " + libPath + ": " + getDlError());
    }

}
template<typename T>
arc::DLLoader<T>::~DLLoader()
{
    if (_handle) {
        dlclose(_handle);
    }
}
template<typename T>
void *arc::DLLoader<T>::getFunction(void *handle, std::string functionName) const 
{
    void *function = dlsym(handle, functionName.c_str());
    if (function == nullptr) {
        throw std::runtime_error("Error in loading of " + libPath + ": " + getDlError());
    }
    return function;
}
template<typename T>
std::string arc::DLLoader<T>::getDlError() const
{
    return dlerror();
}

template<typename T>
void *arc::DLLoader<T>::getHandle() const
{
    return _handle;
}

template<typename T>
bool arc::DLLoader<T>::isGraphical() const
{
    if (libPath.find("arcade_ndk++.so") != std::string::npos ||
        libPath.find("arcade_aalib.so") != std::string::npos ||
        libPath.find("arcade_libcaca.so") != std::string::npos ||
        libPath.find("arcade_allegro5.so") != std::string::npos ||
        libPath.find("arcade_xlib.so") != std::string::npos ||
        libPath.find("arcade_gtk+.so") != std::string::npos ||
        libPath.find("arcade_sfml.so") != std::string::npos ||
        libPath.find("arcade_irrlicht.so") != std::string::npos ||
        libPath.find("arcade_opengl.so") != std::string::npos ||
        libPath.find("arcade_ncurses.so") != std::string::npos ||
        libPath.find("arcade_vulkan.so") != std::string::npos ||
        libPath.find("arcade_qt5.so") != std::string::npos) {
            return true;
    }
    return false;
}

template class arc::DLLoader<arc::IGraphicLibrary>;