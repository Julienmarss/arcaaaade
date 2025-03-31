/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuManager.cpp
*/

#include "Core/MenuManager.hpp"

arc::MenuManager::MenuManager(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games, std::string username) : _state(arc::ArcadeState::LIB_MENU), _username(username) {
    loadMenus(_libraries, _games);
}

arc::MenuManager::~MenuManager() {
}

void arc::MenuManager::loadMenus(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games) {
    (void)_libraries;
    (void)_games;
    MenuComponent libMenu;
    libMenu.SetTitle("Choose the library");
    libMenu.AddItem("SFML");
    libMenu.AddItem("Ncurses");
    _menus.push_back(libMenu);

    MenuComponent gameMenu;
    gameMenu.SetTitle("Choose the game");
    gameMenu.AddItem("Pacman");
    gameMenu.AddItem("Nibbler");
    gameMenu.AddItem("Snake");
    _menus.push_back(gameMenu);

    MenuComponent usernameMenu;
    usernameMenu.SetTitle("Change username");
    usernameMenu.AddItem(_username);
    _menus.push_back(usernameMenu);

    MenuComponent playingMenu;
    playingMenu.SetTitle("Playing as ");
    _menus.push_back(playingMenu);
}

bool arc::MenuManager::processEvent(Event event, char key) {
    if (_state == arc::ArcadeState::LIB_MENU) {
        if (event == Event::UP) {
            _menus[0].Select(_menus[0].GetSelectedIndex() - 1);
        } else if (event == Event::DOWN) {
            _menus[0].Select(_menus[0].GetSelectedIndex() + 1);
        } else if (event == Event::ENTER) {
            _state = arc::ArcadeState::GAME_MENU;
            replaceCurrentTitleMenu("You have " + _menus[0].GetSelectedItem() + " library. You can now select a game.");
        } else if (event == Event::ESCAPE) {
            return false;
        }
    } else if (_state == arc::ArcadeState::GAME_MENU) {
        if (event == Event::UP) {
            _menus[1].Select(_menus[1].GetSelectedIndex() - 1);
        } else if (event == Event::DOWN) {
            _menus[1].Select(_menus[1].GetSelectedIndex() + 1);
        } else if (event == Event::ENTER) {
            _state = arc::ArcadeState::CHANGE_USERNAME;
            replaceCurrentTitleMenu("Playing " + _menus[1].GetSelectedItem() + ". You can now change your username.");
        } else if (event == Event::ESCAPE) {
            replaceCurrentTitleMenu("Choose the library");
            _state = arc::ArcadeState::LIB_MENU;
        }
    } else if (_state == arc::ArcadeState::CHANGE_USERNAME) {
        if (event == Event::TEXT_INPUT && key != 0) {
            if (this->isValidKey(key)) {
                _username += key;
                updateUsername(_username);
            } else {
                replaceCurrentTitleMenu("Invalid character. Please use letters and numbers only.");
            }
        } else if (event == Event::ENTER) {
            _state = arc::ArcadeState::IN_GAME;
            // auto game = _games.at(_menus[1].GetSelectedIndex()).get();
            // std::cout << "Loading game: " << game->GetName() << std::endl;
            //this->_gameManager.LoadGame(_username, game);
        } else if (event == Event::ESCAPE) {
            replaceCurrentTitleMenu("Choose the game");
            _state = arc::ArcadeState::GAME_MENU;
        } else if (event == Event::BACKSPACE) {
            if (!_username.empty()) {
                _username.pop_back();
                updateUsername(_username);
            }
        } else if (event == Event::DELETE) {
            if (!_username.empty()) {
                _username.erase(_username.size() - 1);
                updateUsername(_username);
            }
        }
    } else if (_state == arc::ArcadeState::IN_GAME) {
        if (event == Event::ESCAPE) {
            _state = arc::ArcadeState::CHANGE_USERNAME;
            replaceCurrentTitleMenu("Choose the game");
        }
    } else {
        throw ApplicationError("No menu available in the current state.");
    }
    return true;
}

const arc::MenuComponent& arc::MenuManager::getCurrentMenu() const {
    if (_state == arc::ArcadeState::LIB_MENU)
        return _menus[0];
    else if (_state == arc::ArcadeState::GAME_MENU)
        return _menus[1];
    else if (_state == arc::ArcadeState::CHANGE_USERNAME)
        return _menus[2];
    if (_state == arc::ArcadeState::IN_GAME)
        return _menus[3];
    
    return _menus[0];
}

arc::ArcadeState arc::MenuManager::getState() const {
    return _state;
}

bool arc::MenuManager::isValidKey(char key) const {
    return (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9');
}
void arc::MenuManager::setState(arc::ArcadeState newState) {
    _state = newState;
}


void arc::MenuManager::replaceCurrentTitleMenu(const std::string &title) {
    if (_state == arc::ArcadeState::LIB_MENU) {
        _menus[0].SetTitle(title);
    } else if (_state == arc::ArcadeState::GAME_MENU) {
        _menus[1].SetTitle(title);
    } else if (_state == arc::ArcadeState::CHANGE_USERNAME) {
        _menus[2].SetTitle(title);
    } else if (_state == arc::ArcadeState::IN_GAME) {
        _menus[3].SetTitle(title);
    } else {
        throw ApplicationError("No menu available in the current state.");
    }
}

void arc::MenuManager::setUsername(const std::string &username) {
    _username = username;
}

const std::string& arc::MenuManager::getUsername() const {
    return _username;
}
void arc::MenuManager::updateUsername(const std::string &username) {
    _menus[2].RemoveItem(_menus[2].GetSelectedItem());
    _menus[2].AddItem(username);
    replaceCurrentTitleMenu("Playing " + _menus[1].GetSelectedItem() + ". You can now change your username.");
}

const std::vector<std::vector<arc::RenderComponent>> arc::MenuManager::getCurrentMap() const {
    return this->_gameManager.getCurrentMap();
}

int arc::MenuManager::getCurrentScore() const {
    return this->_gameManager.getCurrentScore();
}