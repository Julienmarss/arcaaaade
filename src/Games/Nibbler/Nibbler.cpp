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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    _gameName = "Nibbler";
}

arc::games::Nibbler::~Nibbler()
{
}

void arc::games::Nibbler::changePlayerPosition(int x, int y)
{
    std::vector<std::pair<int, int>> oldPositions = _snake;
    this->_map[_snake[0].first][_snake[0].second]->SetType(arc::TypeComponent::EMPTY);
    this->_map[_snake[0].first][_snake[0].second]->SetCharacter(' ');
    _snake[0].first += x;
    _snake[0].second += y;
    _playerHead = _snake[0];

    this->_map[_snake[0].first][_snake[0].second]->SetType(arc::TypeComponent::PLAYER);
    this->_map[_snake[0].first][_snake[0].second]->SetCharacter('O');
    
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
    _score += 10;
}

bool arc::games::Nibbler::isValidPosition(int x, int y) const
{
    if (x < 0 || x >= static_cast<int>(_map.size()) ||
        y < 0 || y >= static_cast<int>(_map[0].size())) {
        return false;
    }
    
    if (_map[x][y]->GetType() == arc::TypeComponent::WALL ||
        (_map[x][y]->GetType() == arc::TypeComponent::PLAYER && 
         _map[x][y]->GetCharacter() == 'o')) {
        return false;
    }
    
    return true;
}

bool arc::games::Nibbler::isIntersection(int x, int y) const
{
    int validDirs = 0;
    
    if (x > 0 && _map[x-1][y]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    if (x < static_cast<int>(_map.size())-1 && _map[x+1][y]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    if (y > 0 && _map[x][y-1]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    if (y < static_cast<int>(_map[0].size())-1 && _map[x][y+1]->GetType() != arc::TypeComponent::WALL)
        validDirs++;
    return validDirs > 2;
}

bool arc::games::Nibbler::autoTurn(int nextX, int nextY)
{
    (void)nextX;
    (void)nextY;

    if (_directionX != 0) { 
        if (isValidPosition(_playerHead.first, _playerHead.second - _directionX)) {
            _directionY = -_directionX;
            _directionX = 0;
            return true;
        } else if (isValidPosition(_playerHead.first, _playerHead.second + _directionX)) {
            _directionY = _directionX;
            _directionX = 0;
            return true;
        }
    } else {
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
    
    return false;
}

void arc::games::Nibbler::InitGame()
{
    _snake.clear();
    _score = 0;
    _directionX = 0;
    _directionY = 0;
    _gameOver = false;
    _canTurn = true;
    
    if (_map.empty() || _map[0].empty()) {
        std::cerr << "Creating default map for Nibbler" << std::endl;
        
        int width = 20;
        int height = 12;
        _map.resize(height);
        
        for (int i = 0; i < height; i++) {
            _map[i].resize(width);
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height-1 || j == 0 || j == width-1) {
                    _map[i][j] = std::make_shared<arc::RenderComponent>(i, j, arc::TypeComponent::WALL, '#', "ressources/wall.png");
                } else {
                    _map[i][j] = std::make_shared<arc::RenderComponent>(i, j, arc::TypeComponent::EMPTY, ' ', "ressources/empty.png");
                }
            }
        }
    }
    std::cout << "Initializing Nibbler with map of size " << _map.size() << "x" << _map[0].size() << std::endl;
    
    bool foundHead = false;
    for (size_t i = 0; i < this->_map.size() && !foundHead; ++i) {
        for (size_t j = 0; j < this->_map[i].size() && !foundHead; ++j) {
            if (this->_map[i][j]->GetType() == arc::TypeComponent::PLAYER) {
                _playerHead = std::make_pair(i, j);
                _snake.push_back(_playerHead);
                this->_map[i][j]->SetCharacter('O');
                foundHead = true;
                std::cout << "Found existing player head at " << i << "," << j << std::endl;
            }
        }
    }
    
    for (int i = 1; i < 4; i++) {
        int newX = _playerHead.first + i;
        if (newX < static_cast<int>(_map.size()) && 
            this->_map[newX][_playerHead.second]->GetType() != arc::TypeComponent::WALL) {
            this->_map[newX][_playerHead.second]->SetType(arc::TypeComponent::PLAYER);
            this->_map[newX][_playerHead.second]->SetCharacter('o');
            this->_snake.push_back(std::make_pair(newX, _playerHead.second));
        }
    }
    
    _copy = _map;
    
    _foodCount = countFood();
    
    if (_foodCount == 0) {
        for (int i = 0; i < 5; i++) {
            spawnFood();
        }
    }
    
    std::cout << "Nibbler initialized with snake of length: " << _snake.size() << std::endl;
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

    do {
        x = rand() % _map.size();
        y = rand() % _map[0].size();
        attempts++;
        if (attempts > MAX_ATTEMPTS) {
            return;
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
    
    if (_directionX == 0 && _directionY == 0) {
        _directionX = 0;
        _directionY = 1;
        return true;
    }

    if (_canTurn && isIntersection(_playerHead.first, _playerHead.second)) {
        switch (key) {
            case Event::LEFT:
                if (_directionX != 0) {
                    _directionY = -_directionX;
                    _directionX = 0;
                } else {
                    _directionX = -_directionY;
                    _directionY = 0;
                }
                _canTurn = false;
                break;
            case Event::RIGHT:
                if (_directionX != 0) {
                    _directionY = _directionX;
                    _directionX = 0;
                } else {
                    _directionX = _directionY;
                    _directionY = 0;
                }
                _canTurn = false;
                break;
            default:
                break;
        }
    } else if (!isIntersection(_playerHead.first, _playerHead.second)) {
        _canTurn = true;
    }
    
    int nextX = _playerHead.first + _directionX;
    int nextY = _playerHead.second + _directionY;
    if (!isValidPosition(nextX, nextY)) {
        if (_map[nextX][nextY]->GetType() == arc::TypeComponent::WALL) {
            if (!autoTurn(nextX, nextY)) {
                _gameOver = true;
                return false;
            }
            nextX = _playerHead.first + _directionX;
            nextY = _playerHead.second + _directionY;
        } else {
            _gameOver = true;
            return false;
        }
    }
    if (_map[nextX][nextY]->GetType() == arc::TypeComponent::COLLECTIBLE) {
        changePlayerPosition(_directionX, _directionY);
        addSnakePart(nextX, nextY);
        _foodCount--;
        
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
    this->_map = this->_copy;
    InitGame();
}

std::string arc::games::Nibbler::GetName() const
{
    return "Nibbler";
}

void arc::games::Nibbler::CloseGame()
{
    this->_map.clear();
    this->_copy.clear();
    this->_snake.clear();
}

void arc::games::Nibbler::AddMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map)
{
    this->_map = map;
    this->_copy = map;
}

std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> arc::games::Nibbler::GetMap() const
{
    return this->_map;
}