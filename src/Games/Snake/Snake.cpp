/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Snake.cpp
*/
#include "Games/Snake/Snake.hpp"
#include "Interface/IGameLibrary.hpp"
#include "Core/Click.hpp"
#include "Core/Event.hpp"
#include "Core/Components/RenderComponent.hpp"
#include <vector>
#include <iostream>

extern "C" void *entryPoint() {
    return new arc::games::Snake();
}

arc::games::Snake::Snake()
{
}

arc::games::Snake::~Snake()
{
}

void arc::games::Snake::changePlayerPosition(int x, int y)
{
    std::vector<std::pair<int, int>> oldPositions = _snake;
    
    this->_map[_snake[0].first][_snake[0].second].SetType(arc::TypeComponent::EMPTY);
    this->_map[_snake[0].first][_snake[0].second].SetCharacter(' ');
    
    _snake[0].first += x;
    _snake[0].second += y;
    _playerHead = _snake[0];

    this->_map[_snake[0].first][_snake[0].second].SetType(arc::TypeComponent::PLAYER);
    this->_map[_snake[0].first][_snake[0].second].SetCharacter('O');
    
    for (size_t i = 1; i < _snake.size(); i++) {
        this->_map[_snake[i].first][_snake[i].second].SetType(arc::TypeComponent::EMPTY);
        this->_map[_snake[i].first][_snake[i].second].SetCharacter(' ');
        _snake[i] = oldPositions[i - 1];
        this->_map[_snake[i].first][_snake[i].second].SetType(arc::TypeComponent::PLAYER);
        this->_map[_snake[i].first][_snake[i].second].SetCharacter('o');
    }
}

void arc::games::Snake::addSnakePart(int x, int y)
{
    std::pair<int, int> newPart = {x, y};
    _snake.push_back(newPart);
    
    this->_map[x][y].SetType(arc::TypeComponent::PLAYER);
    this->_map[x][y].SetCharacter('o');
    _score++;
}

void arc::games::Snake::InitGame()
{
    _snake.clear();
    _score = 0;
    _directionX = 0;
    _directionY = 0;
    _gameOver = false;
    
    for (size_t i = 0; i < this->_map.size(); ++i) {
        for (size_t j = 0; j < this->_map[i].size(); ++j) {
            if (this->_map[i][j].GetType() == arc::TypeComponent::PLAYER) {
                _playerHead = std::make_pair(i, j);
                _snake.push_back(_playerHead);
                this->_map[i][j].SetCharacter('O');
                break;
            }
        }
    }
    
    for (int i = 1; i < 3; i++) {
        if (_playerHead.first + i < static_cast<int>(this->_map.size())) {
            this->_map[_playerHead.first + i][_playerHead.second].SetType(arc::TypeComponent::PLAYER);
            this->_map[_playerHead.first + i][_playerHead.second].SetCharacter('o');
            this->_snake.push_back(std::make_pair(_playerHead.first + i, _playerHead.second));
        }
    }
}
void arc::games::Snake::spawnFood()
{
    int x, y;
    do {
        x = rand() % _map.size();
        y = rand() % _map[0].size();
    } while (_map[x][y].GetType() != arc::TypeComponent::EMPTY);
    
    this->_map[x][y].SetType(arc::TypeComponent::COLLECTIBLE);
    this->_map[x][y].SetCharacter('F');
    this->_map[x][y].SetFilePath("resources/food.png");
}

bool arc::games::Snake::Update(click state, Event key)
{
    (void)state;
    
    if (_directionX == 0 && _directionY == 0) {
        switch (key) {
            case Event::UP:    _directionX = -1; _directionY = 0; break;
            case Event::DOWN:  _directionX = 1;  _directionY = 0; break;
            case Event::LEFT:  _directionX = 0;  _directionY = -1; break;
            case Event::RIGHT: _directionX = 0;  _directionY = 1; break;
            default: break;
        }
        return true;
    }
    switch (key) {
        case Event::UP:
            if (_directionX != 1) { _directionX = -1; _directionY = 0; }
            break;
        case Event::DOWN:
            if (_directionX != -1) { _directionX = 1; _directionY = 0; }
            break;
        case Event::LEFT:
            if (_directionY != 1) { _directionX = 0; _directionY = -1; }
            break;
        case Event::RIGHT:
            if (_directionY != -1) { _directionX = 0; _directionY = 1; }
            break;
        default:
            break;
    }
    
    int nextX = _playerHead.first + _directionX;
    int nextY = _playerHead.second + _directionY;
    if (nextX < 0 || nextX >= static_cast<int>(_map.size()) ||
        nextY < 0 || nextY >= static_cast<int>(_map[0].size())) {
        this->_gameOver = true;
        return false;
    }
    if (_map[nextX][nextY].GetType() == arc::TypeComponent::PLAYER && 
        _map[nextX][nextY].GetCharacter() == 'o') {
        this->_gameOver = true;
        return false;
    }
    if (_map[nextX][nextY].GetType() == arc::TypeComponent::COLLECTIBLE) {
        changePlayerPosition(_directionX, _directionY);
        addSnakePart(nextX, nextY);
        spawnFood();
    } else if (_map[nextX][nextY].GetType() == arc::TypeComponent::EMPTY) {
        changePlayerPosition(_directionX, _directionY);
    }
    
    return true;
}
void arc::games::Snake::AddObject(std::string name, arc::RenderComponent)
{
    (void)name;
}

void arc::games::Snake::DeleteObject(std::string name)
{
    (void)name;
}

std::vector<arc::RenderComponent> arc::games::Snake::GetObjects(std::string name) const
{
    (void)name;
    return std::vector<arc::RenderComponent>();
}

int arc::games::Snake::GetScore() const
{
    return this->_score;
}

bool arc::games::Snake::IsGameOver() const
{
    return this->_gameOver;
}

void arc::games::Snake::Reset()
{
    this->_gameOver = false;
    this->_score = 0;
    this->_snake.clear();
    this->_playerHead = std::make_pair(0, 0);
    for (size_t i = 0; i < this->_map.size(); ++i) {
        for (size_t j = 0; j < this->_map[i].size(); ++j) {
            this->_map[i][j].SetType(arc::TypeComponent::EMPTY);
            this->_map[i][j].SetCharacter(' ');
        }
    }
}

std::string arc::games::Snake::GetName() const
{
    return "Snake";
}

void arc::games::Snake::CloseGame()
{
}

void arc::games::Snake::AddMap(std::vector<std::vector<arc::RenderComponent>> map)
{
    this->_map = map;
}

std::vector<std::vector<arc::RenderComponent>> arc::games::Snake::GetMap() const
{
    return this->_map;
}