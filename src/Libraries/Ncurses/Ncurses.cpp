/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** Ncurses.cpp
*/

#include "Libraries/Ncurses/Ncurses.hpp"
#include "Interface/IGraphicLibrary.hpp"
#include "Core/Components/RenderComponent.hpp"
#include "Core/Components/TextComponent.hpp"
#include "Core/Components/MenuComponent.hpp"
#include "Core/Event.hpp"
#include "Libraries/Ncurses/NcursesWrapper.hpp"
#include <ncurses.h>


extern "C" void *entryPoint() {
    return new arc::display::Ncurses();
}
arc::display::Ncurses::Ncurses()
{
}

arc::display::Ncurses::~Ncurses()
{
}
void arc::display::Ncurses::Initialize()
{
    std::cout << "Ncurses Initialize" << std::endl;
}

void arc::display::Ncurses::Display()
{
}

void arc::display::Ncurses::Close()
{
    NcursesWrapper::end();
    std::cout << "Ncurses Close" << std::endl;
}

Event arc::display::Ncurses::HandleEvent()
{
    Event event = Event::TEXT_INPUT;
    int key = NcursesWrapper::getChar();
    if (key == ERR) {
        this->key = 0;
        return Event::TEXT_INPUT;
    }
    this->key = (char) key;
    switch (key) {
        case KEY_UP:
            event = Event::UP;
            break;
        case KEY_DOWN:
            event = Event::DOWN;
            break;
        case KEY_LEFT:
            event = Event::LEFT;
            break;
        case KEY_RIGHT:
            event = Event::RIGHT;
            break;
        case '\n':
            event = Event::ENTER;
            break;
        case 27:
            event = Event::ESCAPE;
            break;
        case KEY_BACKSPACE:
        case 127:
        case 8:
            event = Event::BACKSPACE;
            break;
        case KEY_DC:
            event = Event::DELETE;
            break;
        case 'q':
        case 'Q':
            event = Event::PREVIOUS_LIB;
            this->key = 0;
            break;
        case 'D':
        case 'd':
            event = Event::NEXT_LIB;
            this->key = 0;
            break;
        case 'F':
        case 'f':
            event = Event::PREVIOUS_GAME;
            this->key = 0;
            break;
        case 'H':
        case 'h':
            event = Event::NEXT_GAME;
            this->key = 0;
            break;
        case 'r':
        case 'R':
            event = Event::RESET;
            this->key = 0;
            break;
        default:
            break;
    }

    return event;
}

char arc::display::Ncurses::GetKeyPressed()
{
    if (this->key == ERR)
        return 0;
    return this->key;
}

void arc::display::Ncurses::DrawComponent(std::shared_ptr<arc::RenderComponent> component)
{
    NcursesWrapper::setAttr(2);
    NcursesWrapper::printChar(component->GetX() + 10, component->GetY() + this->middle, component->GetCharacter());
    NcursesWrapper::unsetAttr(2);
}

void arc::display::Ncurses::DrawMap(std::vector<std::vector<std::shared_ptr<arc::RenderComponent>>> map)
{
    NcursesWrapper::clear();
    this->middle = (getmaxx(stdscr) / 2) - (map[0].size() / 2);
    for (auto &line : map) {
        for (auto &component : line) {
            this->DrawComponent(component);
        }
    }
    NcursesWrapper::refresh();
}

void arc::display::Ncurses::DrawText(std::shared_ptr<arc::TextComponent> text)
{
    if (text->GetX() == 0 && text->GetY() == 0) {
        text->SetY((NcursesWrapper::getMaxY() / 2) - (text->GetText().size() / 2));
    }
    if (text->GetX() % 25 == 0) {
        text->SetX((NcursesWrapper::getMaxX() / 2) - (text->GetText().size() / 2));
    }
    if (text->GetY() % 25 == 0) {
        text->SetY((NcursesWrapper::getMaxY() / 2) - (text->GetText().size() / 2));
    }
    NcursesWrapper::print(text->GetX(), text->GetY(), text->GetText(), "");
}

void arc::display::Ncurses::DrawMenu(std::shared_ptr<arc::MenuComponent> menu)
{
    int size = NcursesWrapper::getMaxX();
    int y = NcursesWrapper::getMaxY();
    int i = (y / 2) - (menu->GetItems().size() / 2);
    int x = (size / 2) - (menu->GetTitle()->GetText().size() / 2);
    NcursesWrapper::setAttr(1);
    NcursesWrapper::print(x, i, menu->GetTitle()->GetText());
    i++;
    for (auto &item : menu->GetItems()) {
        if (menu->GetSelectedItem()->GetText() == item->GetText())
            NcursesWrapper::print(x, i, "> %s \n", item->GetText());
        else
            NcursesWrapper::print(x, i, "  %s \n", item->GetText());
        i++;
    }
    NcursesWrapper::unsetAttr(1);
    NcursesWrapper::refresh();
}

std::string arc::display::Ncurses::GetName() const
{
    return "Ncurses";
}

void arc::display::Ncurses::Clear()
{
    NcursesWrapper::clear();
}

bool arc::display::Ncurses::IsOpen()
{
    return true;
}

std::pair<int, int> arc::display::Ncurses::GetMousePos() const
{
    return std::pair<int, int>(0, 0);
}

arc::click arc::display::Ncurses::GetMouseState() const
{
    return arc::click::NOTHING;
}

void arc::display::Ncurses::DrawComponents(std::vector<std::shared_ptr<arc::RenderComponent>> components)
{
    for (auto &component : components) {
        this->DrawComponent(component);
    }
}

void arc::display::Ncurses::Open()
{
    std::cout << "Ncurses open" << std::endl;
    NcursesWrapper::init();
    NcursesWrapper::setupWindow();
}

void arc::display::Ncurses::DrawScore(const int &score, std::shared_ptr<arc::TextComponent> text)
{
    NcursesWrapper::setAttr(1);
    NcursesWrapper::print(text->GetX(), text->GetY(), text->GetText() + " : " + std::to_string(score));
    NcursesWrapper::unsetAttr(1);
    NcursesWrapper::refresh();
}
void arc::display::Ncurses::LaunchMusic(std::string filepath)
{
    (void)filepath;
}

void arc::display::Ncurses::StopMusic(std::string filepath)
{
    (void)filepath;
}

void arc::display::Ncurses::LoadResources(std::string filepath, type type)
{
    (void)filepath;
    (void)type;
}

void arc::display::Ncurses::UnloadResources(std::string filepath, type type)
{
    (void)filepath;
    (void)type;
}