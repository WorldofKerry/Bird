#include <modern/lib.hpp>

#include <fmt/format.h>

#include <iostream>
#include <vector>
#include <tuple>

int main()
{
    std::vector<double> input = {1.2, 2.3, 3.4, 4.5};

    auto [mean, moment] = accumulate_vector(input);

    fmt::print("Mean: {}, Moment: {}\n", mean, moment);

    auto keyboard = KeyboardHandler();
    keyboard.setup();

    while (1)
    {
        std::cout << toString(keyboard.loop()) << std::endl;
    }

    return 0;
}
