/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ApplicationException.cpp
*/

#include "Core/ApplicationError.hpp"

arc::ApplicationError::ApplicationError(std::string const &message, std::string const &component)
{
    _message = message;
    _component = component;
}

const char *arc::ApplicationError::what() const noexcept
{
    return _message.c_str();
}
