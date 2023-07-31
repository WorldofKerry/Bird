#include <modern/display.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <stdexcept>

char stateToChar(int state)
{
    switch (state)
    {
    case (0):
        return '`';
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
    static int pipeCounter = 0;
    static int score = 0;

    curPosition += vertSpeed;
    vertSpeed -= 1;
    curPosition = std::max(0, curPosition);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == height - 1 - curPosition && j == 5)
            {
                if (canvas[j][height - 1 - i] == PIPE_CHAR)
                {
                    auto msg = std::string("u ded, u got ") + std::to_string(score);
                    throw std::runtime_error(msg);
                }
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

    if (++pipeCounter == 7)
    {
        addPipe();
        pipeCounter = 0;
    }

    ++score;
}

void Gui::addPipe()
{
    static int easiness = 15;
    static int counter = 0;

    std::random_device seed;
    std::mt19937 gen{seed()};
    std::uniform_int_distribution<> dist{0, height / 2};

    auto col = canvas[canvas.size() - 1];

    auto bottomHeight = dist(gen);
    auto topHeight = dist(gen);

    if (topHeight + bottomHeight > col.size() - easiness)
    {
        bottomHeight -= 2;
        topHeight -= 2;
        printf("easified\n");
    }

    for (int i = 0; i < bottomHeight; ++i)
    {
        col[i] = PIPE_CHAR;
    }
    for (int i = col.size() - 1 - topHeight; i < col.size(); ++i)
    {
        col[i] = PIPE_CHAR;
    }

    canvas[canvas.size() - 1] = col;

    if (++counter == 10)
    {
        --easiness;
        counter = 0;
    }
}

void Gui::jump()
{
    vertSpeed = 2;
}