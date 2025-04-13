/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** ScoreboardManager.cpp
*/

#include "Core/ScoreboardManager.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Interface/IGraphicLibrary.hpp"
#include "Core/Color.hpp"

void arc::ScoreboardManager::addScore(const std::string &game, const std::string &player, int score)
{
    if (score < 0) {
        std::cerr << "Invalid score: " << score << std::endl;
        return;
    }
    auto it = std::find_if(_scores[game].begin(), _scores[game].end(),
                           [&player](const std::pair<std::string, int> &p)
                           { return p.first == player; });
    if (it != _scores[game].end()) {
        it->second = score;
        std::cout << "Score updated: " << game << " " << player << " " << score << std::endl;
        return;
    }
    _scores[game].emplace_back(player, score);
    std::cout << "Score added: " << game << " " << player << " " << score << std::endl;
}
void arc::ScoreboardManager::loadScoresFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for reading" << std::endl;
        return;
    }
    std::string line;
    try {
        // format: game_name player_name score \n
        while (std::getline(file, line)) {
            if (line.empty())
                continue;
        
            std::string game = line.substr(0, line.find(' '));
            std::string player = line.substr(line.find(' ') + 1, line.rfind(' ') - line.find(' ') - 1);
            std::string scoreStr = line.substr(line.rfind(' ') + 1);
            int score = std::stoi(scoreStr);
            _scores[game].emplace_back(player, score);
        }
        file.close();
        for (auto &game : _scores){
            std::sort(game.second.begin(), game.second.end(), [](const auto &a, const auto &b)
                    { return a.second > b.second; });
        }
    } catch (const std::exception &e) {
        std::cerr << "Error reading score file: " << e.what() << std::endl;
    }
}

void arc::ScoreboardManager::saveScoresToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing" << std::endl;
        return;
    }
    for (const auto &game : _scores) {
        for (const auto &score : game.second) {
            file << game.first << " " << score.first << " " << score.second << "\n";
        }
    }
    file.close();
}
std::vector<std::pair<std::string, int>> arc::ScoreboardManager::getScores(const std::string &game) const
{
    auto it = _scores.find(game);
    if (it != _scores.end())
    {
        std::vector<std::pair<std::string, int>> scores = it->second;
        std::sort(scores.begin(), scores.end(), [](const auto &a, const auto &b)
                  { return a.second > b.second; });
        return scores;
    }
    return {};
}

void arc::ScoreboardManager::printScores(const std::string &game, arc::IGraphicLibrary *library)
{
    auto it = _scores.find(game);
    if (it != _scores.end()) {
        auto titleText = std::make_shared<arc::TextComponent>(0, 0, "Scores for " + game, Colors::RED);
        titleText->SetCharacterSize(20);
        titleText->SetFont("ressources/font.ttf");
        titleText->SetColor(arc::Colors::RED);
        library->DrawText(titleText);
        int i = 1;
        for (const auto &score : it->second){
            i++;
            auto itemText = std::make_shared<arc::TextComponent>(0, 25 * i, score.first + ": " + std::to_string(score.second), Colors::WHITE);
            itemText->SetCharacterSize(16);
            itemText->SetFont("ressources/font.ttf");
            if (i == 1) {
                itemText->SetColor(arc::Colors::YELLOW);
            } else {
                itemText->SetColor(arc::Colors::WHITE);
            }
            library->DrawText(itemText);
        }
    } else {
        library->DrawText(std::make_shared<arc::TextComponent>(0, 50, "No scores available for " + game));
    }
}