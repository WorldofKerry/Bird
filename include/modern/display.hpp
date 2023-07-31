#pragma once

#include <fstream>

class Gui
{
    int width;
    int height;

public:
    Gui(int width, int height) : width(width), height(height) {}
    void loop(int, std::ofstream &);
};
