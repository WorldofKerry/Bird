#include <modern/display.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <thread>

int main()
{

    auto gui = Gui(90, 30);

    std::thread th([&]()
                   {
        while (1)
        if (std::cin.get() == 'p')
        {
            gui.addPipe();
        } });

    while (1)
    {
        std::ofstream animationFile("animation_output.txt");
        gui.loop(0, animationFile);
        // animationFile.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    
}
