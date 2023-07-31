#include <modern/display.hpp>
#include <fstream>
#include <string>

const int ANIMATION_DELAY = 100; // Milliseconds delay between frames

void printHappyFace(int position, std::ofstream &file)
{
    const std::string happy_face[] = {
        " O  O ",
        "   _  ",
        "  \\_/ "};

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < position; ++j)
            file << ' ';
        file << happy_face[i] << '\n';
    }

    file << std::flush;
}
