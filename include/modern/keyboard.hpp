#pragma once

#include <modern/lib.hpp>

enum Action
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DONE
};

struct KeyboardHandler
{
    void setup();
    Action loop();
    void end();
};