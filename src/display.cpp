#include <modern/display.hpp>
#include <fstream>
#include <string>
#include <iostream>

Gui::Gui(int width, int height) : width(width), height(height), banner(0)
{
    for (int i = 0; i < width; ++i)
    {
        banner = (banner + 1) % 10;
        auto row = std::deque<char>(height, (char)(banner + '0'));
        canvas.push_back(row);
    }
}

void Gui::loop(int position, std::ofstream &file)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            file << canvas[j][height - 1 - i];
        }
        file << '\n';
    }
    file << std::flush;

    canvas.pop_front();
    banner = (banner + 1) % 10;
    canvas.push_back(std::deque<char>(height, (char)(banner + '0')));
}

void Gui::addPipe()
{
    canvas[canvas.size() - 1] = std::deque<char>(height, '=');
}
