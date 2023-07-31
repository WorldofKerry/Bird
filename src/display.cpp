#include <modern/display.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

char stateToChar(int state)
{
    switch (state)
    {
    case (0):
        return '.';
    case (1):
        return '\'';
    }
    return 'E';
}

char Gui::getNextChar()
{
    banner = (banner + 1) % 2;
    return stateToChar(banner);
}

Gui::Gui(int width, int height) : width(width), height(height), banner(0), curPosition(5), vertSpeed(0)
{
    for (int i = 0; i < width; ++i)
    {
        char c = getNextChar();
        auto row = std::deque<char>(height, c);
        canvas.push_back(row);
    }
}

void Gui::loop(int position, std::ofstream &file)
{
    curPosition += vertSpeed;
    vertSpeed -= 1;
    curPosition = std::max(0, curPosition);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == height - 1 - curPosition && j == 5)
            {
                file << '@';
            }
            else
            {
                file << canvas[j][height - 1 - i];
            }
        }
        file << '\n';
    }
    file << std::flush;

    canvas.pop_front();
    char c = getNextChar();
    canvas.push_back(std::deque<char>(height, c));
}

void Gui::addPipe()
{
    canvas[canvas.size() - 1] = std::deque<char>(height, '=');
}

void Gui::jump()
{
    vertSpeed = 2;
}