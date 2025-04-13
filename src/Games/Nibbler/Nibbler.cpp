/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Nibbler.cpp
*/
#include "Games/Nibbler/Nibbler.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/Click.hpp"
#include "Core/Event.hpp"
#include "Core/Components/RenderComponent.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>

extern "C" void *entryPoint() {
    return new arc::games::Nibbler();
}

arc::games::Nibbler::Nibbler() : _foodCount(0), _canTurn(true)
{
    // Initialize random seed for food spawning
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    _gameName = "Nibbler";
}

arc::games::Nibbler::~Nibbler()
{
}

void arc::games::Nibbler::changePlayerPosition(int x, int y)
{
    std::vector<std::pair<int, int>> oldPositions = _snake;
    
    // Remove the head from its current position
    this->_map[_snake[0].first][_snake[0].second]->SetType(arc::TypeComponent::EMPTY);
    this->_map[_snake[0].first][_snake[0].second]->SetCharacter(' ');
    
    // Move the head to the new position
    _snake[0].first += x;
    _snake[0].second += y;
    _playerHead = _snake[0];

    // Update head on the map
    this->_map[_snake[0].first][_snake[0].second]->SetType(arc::TypeComponent::PLAYER);
    this->_map[_snake[0].first][_snake[0].second]->SetCharacter('O');
    
    // Update all body segments
    for (size_t i = 1; i < _snake.size(); i++) {
        this->_map[_snake[i].first][_snake[i].second]->SetType(arc::TypeComponent::EMPTY);
        this->_map[_snake[i].first][_snake[i].second]->SetCharacter(' ');
        _snake[i] = oldPositions[i - 1];
        this->_map[_snake[i].first][_snake[i].second]->SetType(arc::TypeComponent::PLAYER);
        this->_map[_snake[i].first][_snake[i].second]->SetCharacter('o');
    }
}

void arc::games::Nibbler::addSnakePart(int x, int y)
{
    std::pair<int, int> newPart = {x, y};
    _snake.push_back(newPart);
    
    this->_map[x][y]->SetType(arc::TypeComponent::PLAYER);
    this->_map[x][y]->SetCharacter('o');
    _score += 10; // More points for Nibbler compared to Snake
}

bool arc::games::Nibbler::isValidPosition(int x, int y) const
{
    // Check if position is inside the map bounds
    if (x < 0 || x >= static_cast<int>(_map.size()) ||
        y < 0 || y >= static_cast<int>(_map[0].size())) {
        return false;
    }
    
    // Check if position is a wall or a snake segment
    if (_map[x][y]->GetType() == arc::TypeComponent::WALL ||
        (_map[x][y]->GetType() == arc::TypeComponent::PLAYER && 
         _map[x][y]->GetCharacter() == 'o')) {
        return false;
    }
    
    return true;
}

bool arc::games::Nibbler::isIntersection(int x, int y) const
{
    // Count possible directions (excluding walls)
    int validDirs = 0;
    
    // Check all four directions
    if (x > 0 && _map[x-1][y]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    if (x < static_cast<int>(_map.size())-1 && _map[x+1][y]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    if (y > 0 && _map[x][y-1]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    if (y < static_cast<int>(_map[0].size())-1 && _map[x][y+1]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    
    // An intersection has more than 2 possible directions
    return validDirs > 2;
}

bool arc::games::Nibbler::autoTurn(int nextX, int nextY)
{
    (void)nextX;
    (void)nextY;

    if (_directionX != 0) { // Moving vertically
        if (isValidPosition(_playerHead.first, _playerHead.second - _directionX)) {
            _directionY = -_directionX;
            _directionX = 0;
            return true;
        } else if (isValidPosition(_playerHead.first, _playerHead.second + _directionX)) {
            _directionY = _directionX;
            _directionX = 0;
            return true;
        }
    } else { // Moving horizontally
        if (isValidPosition(_playerHead.first - _directionY, _playerHead.second)) {
            _directionX = -_directionY;
            _directionY = 0;
            return true;
        } else if (isValidPosition(_playerHead.first + _directionY, _playerHead.second)) {
            _directionX = _directionY;
            _directionY = 0;
            return true;
        }
    }
    
    // If we can't turn, we're trapped
    return false;
}

void arc::games::Nibbler::InitGame()
{
    _snake.clear();
    _score = 0;
    _directionX = 0;
    _directionY = 0;
    _gameOver = false;
    
    // Si la carte est vide, créons-en une
    if (_map.empty() || _map[0].empty()) {
        std::cerr << "Creating default map for Nibbler" << std::endl;
        
        int width = 20;
        int height = 12;
        _map.resize(height);
        
        for (int i = 0; i < height; i++) {
            _map[i].resize(width);
            for (int j = 0; j < width; j++) {
                // Murs sur les bords
                if (i == 0 || i == height-1 || j == 0 || j == width-1) {
                    _map[i][j] = std::make_shared<arc::RenderComponent>(i, j, arc::TypeComponent::WALL, '#', "ressources/wall.png");
                } else {
                    _map[i][j] = std::make_shared<arc::RenderComponent>(i, j, arc::TypeComponent::EMPTY, ' ', "ressources/empty.png");
                }
            }
        }
        
        // Position initiale du serpent
        int startX = height / 2;
        int startY = width / 2;
        _map[startX][startY]->SetType(arc::TypeComponent::PLAYER);
        _map[startX][startY]->SetCharacter('P');
        _playerHead = std::make_pair(startX, startY);
        _snake.push_back(_playerHead);
    }
    
    // Trouver la tête du serpent
    bool foundHead = false;
    for (size_t i = 0; i < this->_map.size() && !foundHead; ++i) {
        for (size_t j = 0; j < this->_map[i].size() && !foundHead; ++j) {
            if (this->_map[i][j]->GetType() == arc::TypeComponent::PLAYER) {
                _playerHead = std::make_pair(i, j);
                _snake.push_back(_playerHead);
                this->_map[i][j]->SetCharacter('O');
                foundHead = true;
            }
        }
    }
    
    // Si on ne trouve pas de tête, placer un serpent dans une position vide
    if (!foundHead && !_map.empty() && !_map[0].empty()) {
        for (size_t i = 1; i < _map.size() - 1 && !foundHead; ++i) {
            for (size_t j = 1; j < _map[i].size() - 1 && !foundHead; ++j) {
                if (_map[i][j]->GetType() == arc::TypeComponent::EMPTY) {
                    _playerHead = std::make_pair(i, j);
                    _snake.push_back(_playerHead);
                    _map[i][j]->SetType(arc::TypeComponent::PLAYER);
                    _map[i][j]->SetCharacter('O');
                    foundHead = true;
                }
            }
        }
    }
    
    // Si toujours pas de tête après recherche, sortir
    if (_snake.empty()) {
        std::cerr << "Could not find or place player in map" << std::endl;
        return;
    }
    
    // Ajouter des segments de corps
    for (int i = 1; i < 4; i++) {
        if (_playerHead.first + i < static_cast<int>(this->_map.size()) && 
            this->_map[_playerHead.first + i][_playerHead.second]->GetType() != arc::TypeComponent::WALL) {
            this->_map[_playerHead.first + i][_playerHead.second]->SetType(arc::TypeComponent::PLAYER);
            this->_map[_playerHead.first + i][_playerHead.second]->SetCharacter('o');
            this->_snake.push_back(std::make_pair(_playerHead.first + i, _playerHead.second));
        }
    }

    // Faire une copie de la carte initiale pour Reset()
    _copy = _map;

    // Compter la nourriture initiale
    _foodCount = countFood();

    // Si pas de nourriture, en placer
    if (_foodCount == 0) {
        for (int i = 0; i < 5; i++) {
            spawnFood();
        }
    }
    
    std::cout << "Nibbler initialized with map size: " << _map.size() << "x" << _map[0].size() << std::endl;
    std::cout << "Snake length: " << _snake.size() << std::endl;
}

int arc::games::Nibbler::countFood() const
{
    int count = 0;
    for (const auto &row : _map) {
        for (const auto &cell : row) {
            if (cell->GetType() == arc::TypeComponent::COLLECTIBLE) {
                count++;
            }
        }
    }
    return count;
}

void arc::games::Nibbler::spawnFood()
{
    int x, y;
    int attempts = 0;
    const int MAX_ATTEMPTS = 50;

    // Try to find an empty spot for food
    do {
        x = rand() % _map.size();
        y = rand() % _map[0].size();
        attempts++;
        if (attempts > MAX_ATTEMPTS) {
            return; // Avoid infinite loop if map is full
        }
    } while (_map[x][y]->GetType() != arc::TypeComponent::EMPTY);
    
    this->_map[x][y]->SetType(arc::TypeComponent::COLLECTIBLE);
    this->_map[x][y]->SetCharacter('F');
    this->_map[x][y]->SetFilePath("ressources/food.png");
    _foodCount++;
}

bool arc::games::Nibbler::Update(click state, Event key)
{
    (void)state;
    
    // Initialize movement direction if not already set
    if (_directionX == 0 && _directionY == 0) {
        _directionX = 0;
        _directionY = 1; // Start moving right by default
        return true;
    }

    // Handle player input at intersections
    if (_canTurn && isIntersection(_playerHead.first, _playerHead.second)) {
        switch (key) {
            case Event::LEFT:
                if (_directionX != 0) { // Moving vertically
                    _directionY = -_directionX;
                    _directionX = 0;
                } else { // Moving horizontally
                    _directionX = -_directionY;
                    _directionY = 0;
                }
                _canTurn = false; // Prevent multiple turns in one intersection
                break;
            case Event::RIGHT:
                if (_directionX != 0) { // Moving vertically
                    _directionY = _directionX;
                    _directionX = 0;
                } else { // Moving horizontally
                    _directionX = _directionY;
                    _directionY = 0;
                }
                _canTurn = false; // Prevent multiple turns in one intersection
                break;
            default:
                break;
        }
    } else if (!isIntersection(_playerHead.first, _playerHead.second)) {
        _canTurn = true; // Reset turn flag when not at an intersection
    }
    
    // Calculate next position
    int nextX = _playerHead.first + _directionX;
    int nextY = _playerHead.second + _directionY;

    // If hitting a wall, try to auto-turn
    if (!isValidPosition(nextX, nextY)) {
        if (_map[nextX][nextY]->GetType() == arc::TypeComponent::WALL) {
            if (!autoTurn(nextX, nextY)) {
                _gameOver = true;
                return false;
            }
            // Recalculate next position after auto-turn
            nextX = _playerHead.first + _directionX;
            nextY = _playerHead.second + _directionY;
        } else {
            // If hitting own body, game over
            _gameOver = true;
            return false;
        }
    }

    // Handle food collection
    if (_map[nextX][nextY]->GetType() == arc::TypeComponent::COLLECTIBLE) {
        changePlayerPosition(_directionX, _directionY);
        addSnakePart(nextX, nextY);
        _foodCount--;
        
        // If all food collected, spawn more or end level
        if (_foodCount <= 0) {
            for (int i = 0; i < 5; i++) {
                spawnFood();
            }
        }
    } else if (_map[nextX][nextY]->GetType() == arc::TypeComponent::EMPTY) {
        changePlayerPosition(_directionX, _directionY);
    }
    
    return true;
}

void arc::games::Nibbler::AddObject(std::string name, std::shared_ptr<arc::RenderComponent> component)
{
    _objects[name].push_back(component);
}

void arc::games::Nibbler::DeleteObject(std::string name)
{
    _objects.erase(name);
}

std::vector<std::shared_ptr<arc::RenderComponent>> arc::games::Nibbler::GetObjects(std::string name) const
{
    auto it = _objects.find(name);
    if (it != _objects.end()) {
        return it->second;
    }
    return std::vector<std::shared_ptr<arc::RenderComponent>>();
}

int arc::games::Nibbler::GetScore() const
{
    return this->_score;
}

bool arc::games::Nibbler::IsGameOver() const
{
    return this->_gameOver;
}

void arc::games::Nibbler::Reset()
{
    this->_gameOver = false;
    this->_score = 0;
    this->_snake.clear();
    this->_playerHead = std::make_pair(0, 0);
    this->_directionX = 0;
    this->_directionY = 0;
    this->_foodCount = 0;
    this->_canTurn = true;
    
    // Reset map from the copy
    this->_map = this->_copy;
    
    // Re-initialize the game
    InitGame();
}

std::string arc::games::Nibbler::GetName() const
{
    return "Nibbler";
}

void arc::games::Nibbler::CloseGame()
{
    // Clean up any resources or game state
    this->_map.clear();
    this->_copy.clear();
    this->_snake.clear();
}

void arc::games::Nibbler::AddMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map)
{
    this->_map = map;
    this->_copy = map; // Save a copy for Reset()
}

std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> arc::games::Nibbler::GetMap() const
{
    return this->_map;
}