#include <modern/display.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main()
{
    struct termios old_tio, new_tio;
    unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO, &old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio = old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &= (~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    auto gui = Gui(90, 20);
    std::thread th([&]()
                   {
                    while (1) {
        std::ofstream animationFile("animation_output.txt");
        gui.loop(0, animationFile);
        animationFile.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); } });
    do
    {
        c = getchar();
        if (c == 'p')
            gui.addPipe();
        else if (c == 'j')
            gui.jump();
        // printf("%d\n", c);

    } while (c != 'q');

    /* restore the former settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

    return 0;
}
