/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ScoreboardManager.hpp
*/

#ifndef SCOREBOARDMANAGER_HPP
# define SCOREBOARDMANAGER_HPP
#include <string>
#include <vector>
#include <map>
#include <exception>
#include "Interface/IGraphicLibrary.hpp"

#include <memory>

namespace arc {
    class ScoreboardManager {
        public:
            /**
             * @brief Constructs a ScoreboardManager object.
             */
            ScoreboardManager() = default;
            /**
             * @brief Destructor for ScoreboardManager.
             */
            ~ScoreboardManager() = default;
            /**
             * @brief Adds a score for a player in a specific game.
             * 
             * @param game The name of the game.
             * @param player The name of the player.
             * @param score The score to add.
             */
            void addScore(const std::string &game, const std::string &player, int score);
            /**
             * @brief Loads scores from a file.
             * 
             * @param filename The name of the file to load scores from.
             */
            void loadScoresFromFile(const std::string &filename);
            /**
             * @brief Saves scores to a file.
             * 
             * @param filename The name of the file to save scores to.
             */
            void saveScoresToFile(const std::string &filename) const;
            /**
             * @brief Retrieves scores for a specific game.
             * 
             * @param game The name of the game.
             * @return A vector of pairs containing player names and their scores.
             */
            std::vector<std::pair<std::string, int>> getScores(const std::string &game) const;
            /**
             * Prints the scores for a specific game.
             * 
             * @param game The name of the game.
             * @param library The graphic library to use for rendering.
             */
            void printScores(const std::string &game, IGraphicLibrary *library);
        private:
            std::map<std::string, std::vector<std::pair<std::string, int>>> _scores;
    };
    class ScoreboardManagerException : public std::exception {
        public:
            explicit ScoreboardManagerException(const std::string &message) : _message(message) {}
            const char *what() const noexcept override {
                return _message.c_str();
            }
        private:
            std::string _message;
    };
}
#endif