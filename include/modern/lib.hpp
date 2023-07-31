#pragma once

#include <vector>
#include <tuple>
#include <string>

/// \brief Accumulate a vector to produce the mean and the first moment of the distribution.
///
/// This computes the mean and the first moment of a vector of double values.
///
std::tuple<double, double> accumulate_vector(
    const std::vector<double> &values ///< The vector of values
);

#include <boost/preprocessor.hpp>

#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem) \
    case elem:                                                             \
        return BOOST_PP_STRINGIZE(elem);

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)       \
    enum name                                                        \
    {                                                                \
        BOOST_PP_SEQ_ENUM(enumerators)                               \
    };                                                               \
                                                                     \
    inline const char *toString(name v)                              \
    {                                                                \
        switch (v)                                                   \
        {                                                            \
            BOOST_PP_SEQ_FOR_EACH(                                   \
                X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE, \
                name,                                                \
                enumerators)                                         \
        default:                                                     \
            return "[Unknown " BOOST_PP_STRINGIZE(name) "]";         \
        }                                                            \
    }

// enum Action
// {
//     UP,
//     DOWN,
//     LEFT,
//     RIGHT,
//     DONE
// };
DEFINE_ENUM_WITH_STRING_CONVERSIONS(Action, (UP)(Down)(LEFT)(RIGHT)(DONE))

struct KeyboardHandler
{
    void setup();
    Action loop();
    void end();
};

void printHappyFace(int position, std::ofstream &file);
