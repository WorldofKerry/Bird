#include <modern/lib.hpp>
#include <modern/keyboard.hpp>
#include <modern/display.hpp>

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

    auto gui = Gui(60, 30);

    Action action;
    while (1)
    {

        action = keyboard.loop();
        switch (action)
        {
        case (Action::RIGHT):
            position += 1;
            gui.addPipe();
            break;
        case (Action::LEFT):
            position -= 1;
            break;
        }
        // if (action != Action::DONE)
        // {
        printw("%i %i\n", action, position);
        std::ofstream animationFile("animation_output.txt");
        gui.loop(position, animationFile);
        animationFile.close();
        printw("loop\n");
        // }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
