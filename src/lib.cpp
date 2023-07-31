#include <modern/lib.hpp>
#include <modern/display.hpp>
#include <modern/keyboard.hpp>

#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <ncurses.h>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace ba = boost::accumulators;

std::tuple<double, double> accumulate_vector(const std::vector<double> &values)
{

    ba::accumulator_set<double, ba::stats<ba::tag::mean, ba::tag::moment<2>>> acc;

    std::for_each(std::begin(values), std::end(values), std::ref(acc));

    return {ba::mean(acc), ba::moment<2>(acc)};
}

const int ANIMATION_DELAY = 100; // Milliseconds delay between frames

void printHappyFace(int position, std::ofstream &file)
{
    const std::string happy_face[] = {
        " O  O ",
        "   _  ",
        "  \\_/ "};

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < position; ++j)
            file << ' ';
        file << happy_face[i] << '\n';
    }

    file << std::flush;
}
