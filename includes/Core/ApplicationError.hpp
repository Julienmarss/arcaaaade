/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ApplicationError.hpp
*/

#ifndef APPLICATIONERROR_HPP
#define APPLICATIONERROR_HPP

#include <iostream>

namespace arc {
    class ApplicationError : public std::exception
    {
        public:
            ApplicationError(std::string const &message,
                             std::string const &component = "Application");
            ~ApplicationError() noexcept override = default;
            const char *what() const noexcept override;
        private:
            std::string _message;
            std::string _component;
    };
}
#endif