/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ALibraryModule.hpp
*/


#ifndef ALIBRARYMODULE_HPP
# define ALIBRARYMODULE_HPP

#include "Interface/ILibraryModule.hpp"

namespace arc::libraries {
    class ALibraryModule : virtual public ILibraryModule {
        public:
        ALibraryModule() = default;
            virtual void init() = 0;
            virtual void stop() = 0;
            virtual const std::string &getName() const = 0;
            virtual ~ALibraryModule() = default;
        protected:
        private:
    };
}

#endif