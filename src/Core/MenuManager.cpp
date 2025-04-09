/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuManager.cpp
*/

#include "Core/MenuManager.hpp"

arc::MenuManager::MenuManager(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games, std::string username) : _state(arc::ArcadeState::LIB_MENU), _libraries(_libraries),_games(_games), _username(username) {
    loadMenus(_libraries, _games);
}

arc::MenuManager::~MenuManager() {
}

void arc::MenuManager::loadMenus(std::vector<std::shared_ptr<IGraphicLibrary>> _libraries, std::vector<std::shared_ptr<IGameLibrary>> _games) {
    MenuComponent libMenu;
    TextComponent libTitle(100, 100, "Choose the library", arc::Colors::WHITE);
    libTitle.SetCharacterSize(20);
    libMenu.SetTitle(libTitle);
    int i = 0;
    for (const auto& lib : _libraries) {
        TextComponent text(100, 100 + i, lib->GetName(), arc::Colors::WHITE);
        std::cout << "Library name: " << lib->GetName() << std::endl;
        libMenu.AddItem(text);
        i = i + 50;
    }
    _menus.push_back(libMenu);

    MenuComponent gameMenu;
    TextComponent gameTitle(100, 100, "Choose the game", arc::Colors::WHITE);
    gameTitle.SetCharacterSize(20);

    gameMenu.SetTitle(gameTitle);
    i = 0;
    for (const auto& game : _games) {
        TextComponent text(100, 100 + i, game->GetName(), arc::Colors::WHITE);
        gameMenu.AddItem(text);
        i = i + 50;
    }
    _menus.push_back(gameMenu);

    MenuComponent usernameMenu;
    TextComponent usernameTitle(100, 100, "Change username", arc::Colors::WHITE);
    usernameTitle.SetCharacterSize(20);
    usernameMenu.SetTitle(usernameTitle);
    TextComponent username(100, 100 + 50, _username, arc::Colors::WHITE);
    usernameMenu.AddItem(username);
    _menus.push_back(usernameMenu);

    MenuComponent playingMenu;
    TextComponent playingTitle(100, 100, "Playing", arc::Colors::WHITE);
    playingTitle.SetCharacterSize(20);
    TextComponent usernameText(100, 100 + 50, _username, arc::Colors::WHITE);
    playingMenu.SetTitle(playingTitle);
    playingMenu.AddItem(usernameText);
    _menus.push_back(playingMenu);

    this->_libraries = _libraries;
    this->_games = _games;
}

bool arc::MenuManager::processEvent(Event event, char key) {
    if (_state == arc::ArcadeState::LIB_MENU) {
        if (event == Event::UP) {
            _menus[0].Select(_menus[0].GetSelectedIndex() - 1);
        } else if (event == Event::DOWN) {
            _menus[0].Select(_menus[0].GetSelectedIndex() + 1);
        } else if (event == Event::ENTER) {
            _state = arc::ArcadeState::GAME_MENU;
            replaceCurrentTitleMenu("You have " + _menus[0].GetSelectedItem().GetText() + " library. You can now select a game.");
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
            replaceCurrentTitleMenu("Playing " + _menus[1].GetSelectedItem().GetText() + ". You can now change your username.");
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
            IGameLibrary* game = nullptr;
            for (auto& g : _games) {
                if (g->GetName() == _menus[1].GetSelectedItem().GetText()) {
                    game = g.get();
                    break;
                }
            }
            if (game == nullptr) {
                throw ApplicationError("Game not found.");
            }
            IGraphicLibrary* library = nullptr;
            for (auto& l : _libraries) {
                if (l->GetName() == _menus[0].GetSelectedItem().GetText()) {
                    library = l.get();
                    break;
                }
            }
            _gameManager.LoadGame(_username, game, library);
            _game = game;
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
        _menus[0].GetTitle().SetText(title);
    } else if (_state == arc::ArcadeState::GAME_MENU) {
        _menus[1].GetTitle().SetText(title);
    } else if (_state == arc::ArcadeState::CHANGE_USERNAME) {
        _menus[2].GetTitle().SetText(title);
    } else if (_state == arc::ArcadeState::IN_GAME) {
        _menus[3].GetTitle().SetText(title);
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
    std::cout << "Updating username to: " << username << std::endl;
    _menus[2].RemoveItem(_menus[2].GetItems()[0]);
    _menus[2].AddItem(TextComponent(100, 100 + 50, username, arc::Colors::WHITE));
    replaceCurrentTitleMenu("Playing " + _menus[1].GetSelectedItem().GetText() + ". You can now change your username.");
}
const arc::TextComponent arc::MenuManager::getCurrentText() const {
    return this->_gameManager.getCurrentText();
}

const arc::IGameLibrary* arc::MenuManager::getCurrentGame() const {
    return this->_game;
}

arc::IGameLibrary* arc::MenuManager::getCurrentGame() {
    return this->_game;
}