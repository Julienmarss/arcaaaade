/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** MenuManager.cpp
*/

#include "Core/MenuManager.hpp"

arc::MenuManager::MenuManager(std::vector<std::shared_ptr<IGraphicLibrary>> libraries, 
    std::vector<std::shared_ptr<IGameLibrary>> games, 
    std::string username, 
    int selectedLib,
    arc::ScoreboardManager *scoreManager,
    arc::ToggleLibManager *toggleLibManager) 
: _state(arc::ArcadeState::LIB_MENU)
, _libraries(libraries)
, _games(games)
, _game(nullptr)
, _username(username)
, _toggleLibManager(toggleLibManager)
, _scoreboardManager(scoreManager)
{
loadMenus(libraries, games, selectedLib);
}

arc::MenuManager::~MenuManager() {
}

void arc::MenuManager::loadMenus(std::vector<std::shared_ptr<IGraphicLibrary>> libraries, 
                               std::vector<std::shared_ptr<IGameLibrary>> games, 
                               int selectedLib) 
{
    // Library menu
    auto libMenu = std::make_shared<MenuComponent>();
    auto libTitle = std::make_shared<TextComponent>(100, 100, "Choose the library", arc::Colors::WHITE);
    libTitle->SetCharacterSize(20);
    libTitle->SetFont("ressources/font.ttf");
    libMenu->SetTitle(libTitle);
    
    int i = 0;
    for (const auto& lib : libraries) {
        auto text = std::make_shared<TextComponent>(100, 100 + i, lib->GetName(), arc::Colors::WHITE);
        text->SetFont("ressources/font.ttf");
        std::cout << "Library name: " << lib->GetName() << std::endl;
        libMenu->AddItem(text);
        i = i + 50;
    }
    libMenu->Select(selectedLib);
    _menus.push_back(libMenu);

    // Game menu
    auto gameMenu = std::make_shared<MenuComponent>();
    auto gameTitle = std::make_shared<TextComponent>(100, 100, "Choose the game", arc::Colors::WHITE);
    gameTitle->SetCharacterSize(20);
    gameTitle->SetFont("ressources/font.ttf");
    gameMenu->SetTitle(gameTitle);
    
    i = 0;
    for (const auto& game : games) {
        auto text = std::make_shared<TextComponent>(100, 100 + i, game->GetName(), arc::Colors::WHITE);
        text->SetFont("ressources/font.ttf");
        gameMenu->AddItem(text);
        i = i + 50;
    }
    _menus.push_back(gameMenu);

    // Username menu
    auto usernameMenu = std::make_shared<MenuComponent>();
    auto usernameTitle = std::make_shared<TextComponent>(100, 100, "Change username", arc::Colors::WHITE);
    usernameTitle->SetCharacterSize(20);
    usernameTitle->SetFont("ressources/font.ttf");
    usernameMenu->SetTitle(usernameTitle);
    
    auto usernameText = std::make_shared<TextComponent>(100, 150, _username, arc::Colors::WHITE);
    usernameText->SetFont("ressources/font.ttf");
    usernameMenu->AddItem(usernameText);
    _menus.push_back(usernameMenu);

    // Playing menu
    auto playingMenu = std::make_shared<MenuComponent>();
    auto playingTitle = std::make_shared<TextComponent>(100, 100, "Playing", arc::Colors::WHITE);
    playingTitle->SetCharacterSize(20);
    playingTitle->SetFont("ressources/font.ttf");
    
    auto playingUsername = std::make_shared<TextComponent>(100, 150, _username, arc::Colors::WHITE);
    playingUsername->SetFont("ressources/font.ttf");
    playingMenu->SetTitle(playingTitle);
    playingMenu->AddItem(playingUsername);
    _menus.push_back(playingMenu);

    // Game over menu
    auto gameOverMenu = std::make_shared<MenuComponent>();
    auto gameOverTitle = std::make_shared<TextComponent>(100, 100, "Game Over", arc::Colors::WHITE);
    gameOverTitle->SetCharacterSize(20);
    gameOverTitle->SetFont("ressources/font.ttf");

    auto gameOverText = std::make_shared<TextComponent>(100, 150, "Back to games", arc::Colors::WHITE);
    gameOverText->SetFont("ressources/font.ttf");
    gameOverMenu->SetTitle(gameOverTitle);
    gameOverMenu->AddItem(gameOverText);
    _menus.push_back(gameOverMenu); 

    // Store references
    this->_libraries = libraries;
    this->_games = games;
}

bool arc::MenuManager::processEvent(Event event, char key) {
    if (_state == arc::ArcadeState::LIB_MENU) {
        if (event == Event::UP) {
            _menus[0]->Select(_menus[0]->GetSelectedIndex() - 1);
        } else if (event == Event::DOWN) {
            _menus[0]->Select(_menus[0]->GetSelectedIndex() + 1);
        } else if (event == Event::ENTER) {
            
            _toggleLibManager->setNextLib(_menus[0]->GetSelectedIndex());
            _state = arc::ArcadeState::GAME_MENU;
            replaceCurrentTitleMenu("You have " + _menus[0]->GetSelectedItem()->GetText() + " library. You can now select a game.");
        } else if (event == Event::ESCAPE) {
            return false;
        }
    } else if (_state == arc::ArcadeState::GAME_MENU) {
        if (event == Event::UP) {
            _menus[1]->Select(_menus[1]->GetSelectedIndex() - 1);
        } else if (event == Event::DOWN) {
            _menus[1]->Select(_menus[1]->GetSelectedIndex() + 1);
        } else if (event == Event::ENTER) {
            _state = arc::ArcadeState::CHANGE_USERNAME;
            replaceCurrentTitleMenu("Playing " + _menus[1]->GetSelectedItem()->GetText() + ". You can now change your username.");
            updateUsername(_username);
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
                if (g->GetName() == _menus[1]->GetSelectedItem()->GetText()) {
                    game = g.get();
                    break;
                }
            }
            if (game == nullptr) {
                throw ApplicationError("Game not found.");
            }
            _gameManager.LoadGame(game);
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
            _state = arc::ArcadeState::GAME_OVER;
            replaceCurrentTitleMenu("Score: " + std::to_string(_game->GetScore()));
            this->_scoreboardManager->addScore(_game->GetName(), _username, _game->GetScore());
            this->_scoreboardManager->saveScoresToFile("./scores.txt");
        } else if (event == Event::RESET){
            std::cout << "Resetting game..." << std::endl;
            _gameManager.ResetGame();
        } else if (event == Event::NEXT_GAME) {
            std::cout << "Next game..." << std::endl;
            loadNextGame();
        } else if (event == Event::PREVIOUS_GAME) {
            std::cout << "Previous game..." << std::endl;
            loadPreviousGame();
        }
    }else if (_state == arc::ArcadeState::GAME_OVER) {
        if (event == Event::ENTER || event == Event::ESCAPE) {
            _state = arc::ArcadeState::GAME_MENU;
            replaceCurrentTitleMenu("Choose the game");
        }
    } else {
        throw ApplicationError("No menu available in the current state.");
    }
    return true;
}

std::shared_ptr<arc::MenuComponent> arc::MenuManager::getCurrentMenu() const {
    if (_state == arc::ArcadeState::LIB_MENU)
        return _menus[0];
    else if (_state == arc::ArcadeState::GAME_MENU)
        return _menus[1];
    else if (_state == arc::ArcadeState::CHANGE_USERNAME)
        return _menus[2];
    if (_state == arc::ArcadeState::IN_GAME)
        return _menus[3];
    if (_state == arc::ArcadeState::GAME_OVER)
        return _menus[4];
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

void arc::MenuManager::replaceCurrentTitleMenu(const std::string &title)
{
    std::shared_ptr<TextComponent> newTitle;
    
    if (_state == arc::ArcadeState::LIB_MENU) {
        newTitle = std::make_shared<TextComponent>(100, 100, title, arc::Colors::WHITE);
        newTitle->SetCharacterSize(20);
        newTitle->SetFont("ressources/font.ttf");
        _menus[0]->SetTitle(newTitle);
    } else if (_state == arc::ArcadeState::GAME_MENU) {
        newTitle = std::make_shared<TextComponent>(100, 100, title, arc::Colors::WHITE);
        newTitle->SetCharacterSize(20);
        newTitle->SetFont("ressources/font.ttf");
        _menus[1]->SetTitle(newTitle);
    } else if (_state == arc::ArcadeState::CHANGE_USERNAME) {
        newTitle = std::make_shared<TextComponent>(100, 100, title, arc::Colors::WHITE);
        newTitle->SetCharacterSize(20);
        newTitle->SetFont("ressources/font.ttf");
        _menus[2]->SetTitle(newTitle);
    } else if (_state == arc::ArcadeState::IN_GAME) {
        newTitle = std::make_shared<TextComponent>(100, 100, title, arc::Colors::WHITE);
        newTitle->SetCharacterSize(20);
        newTitle->SetFont("ressources/font.ttf");
        _menus[3]->SetTitle(newTitle);
    } else if (_state == arc::ArcadeState::GAME_OVER) {
        newTitle = std::make_shared<TextComponent>(100, 100, title, arc::Colors::WHITE);
        newTitle->SetCharacterSize(20);
        newTitle->SetFont("ressources/font.ttf");
        _menus[4]->SetTitle(newTitle);
    } else {
        std::cout << "State " << _state << " not handled." << std::endl;
        throw ApplicationError("No menu available in the current state.");
    }
}

void arc::MenuManager::setUsername(const std::string &username) {
    _username = username;
}

const std::string& arc::MenuManager::getUsername() const {
    return _username;
}

void arc::MenuManager::updateUsername(const std::string &username)
{
    auto text = std::make_shared<TextComponent>(100, 150, username, arc::Colors::WHITE);
    text->SetFont("ressources/font.ttf");
    if (_menus[2]->GetItems().size() > 0) {
        _menus[2]->RemoveItem(_menus[2]->GetItems()[0]);
    }
    _menus[2]->AddItem(text);
    
    auto title = std::make_shared<TextComponent>(100, 100, 
        "Playing " + _menus[1]->GetSelectedItem()->GetText() + ". You can now change your username.", 
        arc::Colors::WHITE);
    title->SetCharacterSize(20);
    title->SetFont("ressources/font.ttf");
    _menus[2]->SetTitle(title);
}
std::shared_ptr<arc::TextComponent> arc::MenuManager::getCurrentText() const {
    return this->_gameManager.getCurrentText();
}

const arc::IGameLibrary* arc::MenuManager::getCurrentGame() const {
    return this->_game;
}

arc::IGameLibrary* arc::MenuManager::getCurrentGame() {
    return this->_game;
}

void arc::MenuManager::loadNextGame() {
    size_t index = 0;
    for (size_t i = 0; i < _games.size(); i++) {
        if (_games[i]->GetName() == _game->GetName()) {
            index = i;
            break;
        }
    }
    if (index + 1 >= _games.size()) {
        index = 0;
    } else {
        index++;
    }
    _game = _games[index].get();
    _gameManager.LoadGame(_game);
}

void arc::MenuManager::loadPreviousGame() {
    size_t index = 0;
    for (size_t i = 0; i < _games.size(); i++) {
        if (_games[i]->GetName() == _game->GetName()) {
            index = i;
            break;
        }
    }
    if (index == 0) {
        index = _games.size() - 1;
    } else {
        index--;
    }
    _game = _games[index].get();
    _gameManager.LoadGame(_game);
}