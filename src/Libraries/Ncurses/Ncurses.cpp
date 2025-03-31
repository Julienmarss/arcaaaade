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
}

void arc::display::Ncurses::Display()
{
}

void arc::display::Ncurses::Close()
{
    endwin();
}

arc::Event arc::display::Ncurses::HandleEvent()
{
    Event event = arc::Event::TEXT_INPUT;
    int key = getch();
    if (key == ERR) {
        this->key = 0;
        return event;
    }
    this->key = (char) key;
    switch (key) {
        case KEY_UP:
            event = arc::Event::UP;
            break;
        case KEY_DOWN:
            event = arc::Event::DOWN;
            break;
        case KEY_LEFT:
            event = arc::Event::LEFT;
            break;
        case KEY_RIGHT:
            event = arc::Event::RIGHT;
            break;
        case '\n':
            event = arc::Event::ENTER;
            break;
        case 27:
            event = arc::Event::ESCAPE;
            break;
        case KEY_DC:
        case KEY_BACKSPACE:
        case 127:
        case 8:
            event = arc::Event::DELETE;
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

void arc::display::Ncurses::DrawComponent(const arc::RenderComponent &component)
{
    attron(COLOR_PAIR(2));
    mvaddch(component.GetX() + 10, component.GetY() + this->middle, component.GetCharacter());
    mvaddch(component.GetX() + 10, component.GetY() + this->middle, component.GetCharacter());
    attroff(COLOR_PAIR(2));
}

void arc::display::Ncurses::DrawMap(const std::vector<std::vector<arc::RenderComponent>> &map)
{
    clear();
    for (auto &line : map) {
        this->middle = (getmaxx(stdscr) / 2) - (line.size() / 2);
        for (auto &component : line) {
            this->DrawComponent(component);
        }
    }
    refresh();
}

void arc::display::Ncurses::DrawText(const arc::TextComponent &text)
{
    (void)text;
}

void arc::display::Ncurses::DrawMenu(const arc::MenuComponent &menu)
{
    int size = getmaxx(stdscr);
    int y = getmaxy(stdscr);
    int i = (y / 2) - (menu.GetItems().size() / 2);
    int x = (size / 2) - (menu.GetTitle().size() / 2);
    attron(COLOR_PAIR(1));
    mvprintw(i, x, "%s \n", menu.GetTitle().c_str());
    i++;
    for (auto &item : menu.GetItems()) {
        if (menu.GetSelectedItem() == item)
            mvprintw(i + 1, x, "> %s \n", item.c_str());
        else
            mvprintw(i + 1, x, "%s \n", item.c_str());
        i++;
    }
    attroff(COLOR_PAIR(1));
    refresh();
}

std::string arc::display::Ncurses::GetName() const
{
    return "Ncurses";
}

void arc::display::Ncurses::Clear()
{
    clear();
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

void arc::display::Ncurses::DrawComponents(const std::vector<arc::RenderComponent> &components)
{
    for (auto &component : components) {
        this->DrawComponent(component);
    }
}

void arc::display::Ncurses::Open()
{
    std::cout << "Ncurses start" << std::endl;
    initscr();
    nodelay(stdscr, TRUE);
    scroll(stdscr);
    scrollok(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void arc::display::Ncurses::DrawScore(const int &score)
{
    (void)score;
    // mvprintw(0, 0, "Score: %d", score);
}

void arc::display::Ncurses::LaunchMusic(std::string filepath)
{
    (void)filepath;
}

void arc::display::Ncurses::StopMusic(std::string filepath)
{
    (void)filepath;
}

void arc::display::Ncurses::LoadResources(std::string filepath, arc::type type)
{
    (void)filepath;
    (void)type;
}

void arc::display::Ncurses::UnloadResources(std::string filepath, arc::type type)
{
    (void)filepath;
    (void)type;
}