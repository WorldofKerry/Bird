#include <modern/display.hpp>
#include <fstream>
#include <string>

void Gui::loop(int position, std::ofstream &file)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            file << (i + j + position) % 10;
        }
        file << '\n';
    }
    file << std::flush;
}