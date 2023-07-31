#include <modern/keyboard.hpp>

#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <ncurses.h>

Action KeyboardHandler::loop()
{
    if (int ch = getch(); ch != 'q')
    {
        // Check for arrow keys
        switch (ch)
        {
        case KEY_UP:
            return Action::UP;
        case KEY_DOWN:
            return Action::DONE;
        case KEY_LEFT:
            return Action::LEFT;
        case KEY_RIGHT:
            return Action::RIGHT;
        default:
            printw("Press the arrow keys. Press 'q' to quit.\n");
            break;
        }
    }
    refresh();
    return Action::DONE;
}

void KeyboardHandler::end()
{
    // End ncurses
    endwin();
}

void KeyboardHandler::setup()
{
    // Initialize ncurses
    initscr();
    cbreak();             // Line buffering disabled
    noecho();             // Don't echo input characters
    keypad(stdscr, true); // Enable the keypad for arrow keys

    // Print instructions
    printw("Press the arrow keys. Press 'q' to quit.\n");
}