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

    /**
     * @class DLLoader
     * @brief Template class for dynamically loading shared libraries and functions.
     * 
     * This class handles runtime loading of shared libraries and retrieving symbols
     * (such as function pointers) using system dynamic linking tools.
     * 
     * @tparam T The type expected from loaded functions.
     */
    template<typename T>
    class DLLoader
    {
    public:
        /**
         * @brief Constructs a DLLoader and loads the library from the given path.
         * 
         * @param path Path to the dynamic library file.
         */
        DLLoader(const std::string &path);

        /**
         * @brief Destructor that unloads the library if it was loaded.
         */
        ~DLLoader();

        /**
         * @brief Retrieves a function pointer from the loaded library.
         * 
         * @param handle The handle to the dynamic library.
         * @param functionName The name of the function to retrieve.
         * @return A void pointer to the function.
         */
        void *getFunction(void *handle, std::string functionName) const;

        /**
         * @brief Gets the handle to the loaded dynamic library.
         * 
         * @return The handle to the dynamic library.
         */
        void *getHandle() const;

        /**
         * @brief Checks whether the loaded library is a graphical module.
         * 
         * @return True if it's a graphical module, false otherwise.
         */
        bool isGraphical() const;

    private:
        std::string libPath;   ///< Path to the dynamic library.
        void* _handle;         ///< Handle to the dynamic library.

        /**
         * @brief Gets the latest dynamic loading error message.
         * 
         * @return A string describing the last dynamic linking error.
         */
        std::string getDlError() const;
    };

}

#endif // DLLOADER_HPP
