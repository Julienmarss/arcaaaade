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
    /**
     * @brief Custom exception class for handling application-specific errors.
     */
    class ApplicationError : public std::exception
    {
        public:
            /**
             * @brief Constructs a new ApplicationError object.
             * 
             * @param message Description of the error.
             * @param component Component where the error occurred (default: "Application").
             */
            ApplicationError(std::string const &message,
                             std::string const &component = "Application");

            /**
             * @brief Default destructor.
             */
            ~ApplicationError() noexcept override = default;

            /**
             * @brief Returns the error message.
             * 
             * @return const char* C-style string describing the error.
             */
            const char *what() const noexcept override;

        private:
            std::string _message;   ///< Full error message combining message and component.
            std::string _component; ///< Component where the error originated.
    };
}

#endif
