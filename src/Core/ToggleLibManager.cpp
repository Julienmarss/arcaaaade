/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ToggleLibManager.cpp
*/

#include "Core/ToggleLibManager.hpp"

arc::ToggleLibManager::ToggleLibManager(std::vector<std::shared_ptr<IGraphicLibrary>> libraries) : _libraries(libraries)
{
    if (libraries.empty()) {
        throw std::runtime_error("No graphic libraries available");
    }
    this->_nextGraphicLibrary = libraries[0];
    this->isToggle = false;
}

bool arc::ToggleLibManager::isToggleEvent(Event event)
{
    if (this->isToggle == true) {
        return true;
    }
    if (event == Event::PREVIOUS_LIB || event == Event::NEXT_LIB ||
        event == Event::PREVIOUS_GAME || event == Event::NEXT_GAME) {
        if (event == Event::PREVIOUS_LIB) {
            size_t currentIndex = 0;
            for (size_t i = 0; i < _libraries.size(); ++i) {
                if (_libraries[i].get() == _nextGraphicLibrary.get()) {
                    currentIndex = i;
                    break;
                }
            }
            if (currentIndex == 0) {
                _nextGraphicLibrary = _libraries[_libraries.size() - 1];
            } else {
                _nextGraphicLibrary = _libraries[currentIndex - 1];
            }
        } else if (event == Event::NEXT_LIB) {
            size_t currentIndex = 0;
            for (size_t i = 0; i < _libraries.size(); ++i) {
                if (_libraries[i].get() == _nextGraphicLibrary.get()) {
                    currentIndex = i;
                    break;
                }
            }
            if (currentIndex == _libraries.size() - 1) {
                _nextGraphicLibrary = _libraries[0];
            } else {
                _nextGraphicLibrary = _libraries[currentIndex + 1];
            }
        }
        this->_event = event;
        return true;
    }
    return false;
}

std::shared_ptr<arc::IGraphicLibrary> arc::ToggleLibManager::getNextLib()
{
    if (this->_nextGraphicLibrary != nullptr) {
        this->isToggle = false;
        return this->_nextGraphicLibrary;
    }
    return nullptr;
}

arc::ToggleLibManager::~ToggleLibManager()
{
    this->_libraries.clear();
}

void arc::ToggleLibManager::setNextLib(int index)
{
    if (index < 0) {
        index = 0;
    } else if (index >= static_cast<int>(this->_libraries.size())) {
        index = this->_libraries.size() - 1;
    }
    if (index >= 0 && index < static_cast<int>(this->_libraries.size())) {
        if (this->_libraries[index] == this->_nextGraphicLibrary) {
            return;
        }
        this->_nextGraphicLibrary = this->_libraries[index];
        this->isToggle = true;
    } else {
        throw std::out_of_range("Index out of range");
    }
    std::cout << "Next library set to: " << this->_nextGraphicLibrary->GetName() << std::endl;
}

void arc::ToggleLibManager::setCurrentLib(int index)
{
    if (index < 0) {
        index = 0;
    } else if (index >= static_cast<int>(this->_libraries.size())) {
        index = this->_libraries.size() - 1;
    }
    if (index >= 0 && index < static_cast<int>(this->_libraries.size())) {
        this->_nextGraphicLibrary = this->_libraries[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}