#include <modern/lib.hpp>

#include <fmt/format.h>
#include <ncurses.h>

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <thread>

int main()
{
    const int screen_width = 50;               // Width of the console screen
    const int total_frames = screen_width + 5; // Total number of frames for animation
    int position = 0;

    auto keyboard = KeyboardHandler();
    keyboard.setup();

    Action action;
    while (1)
    {

        action = keyboard.loop();
        switch (action)
        {
        case (Action::RIGHT):
            position += 1;
            break;
        case (Action::LEFT):
            position -= 1;
            break;
        }
        if (action != Action::DONE)
        {
            printw("%s %i\n", toString(action), position);
            std::ofstream animationFile("animation_output.txt");
            printHappyFace(position, animationFile);
            // animationFile.close();
            printw("sleeping");
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            printw("done sleep");
        }
    }

    return 0;
}
