#pragma once

#include <fstream>
#include <deque>

class Gui
{
    int width;
    int height;
    int banner;
    int vertSpeed; 
    int curPosition; 
    std::deque<std::deque<char>> canvas;
    char getNextChar(); 

public:
    Gui(int, int);
    void loop(int, std::ofstream &);
    void addPipe();
    void jump(); 
};
