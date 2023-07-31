#pragma once

#include <fstream>
#include <deque>

class Gui
{
    int width;
    int height;
    int banner;
    std::deque<std::deque<char>> canvas;

public:
    Gui(int, int);
    void loop(int, std::ofstream &);
    void addPipe();
};
