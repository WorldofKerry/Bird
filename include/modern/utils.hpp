#include <type_traits>
#include <string>
#include <vector>
#include <set>

template <typename T>
concept CHasToString = requires(T const &x) {
    !std::convertible_to<std::string, T>;

    {
        toString(x)
    } -> std::convertible_to<std::string>;
};

template <CHasToString T>
    requires(!std::is_arithmetic_v<T>)
inline std::ostream &operator<<(std::ostream &stream,
                                T const &x)
{
    return stream << toString(x);
}

template <CHasToString T>
inline std::ostream &operator<<(std::ostream &stream, std::set<T> const &x)
{
    stream << "set{";
    streamJoin(stream, x, ", ");
    stream << "}";

    return stream;
}

template <CHasToString T1, CHasToString T2>
inline std::ostream &operator<<(std::ostream &stream, std::pair<T1, T2> const &x)
{
    stream << "[" << x.first << ", " << x.second << "]";

    return stream;
}

template <CHasToString T>
inline std::ostream &operator<<(std::ostream &stream, std::vector<T> const &xs)
{
    auto iter = xs.begin();
    stream << "[";
    if (iter != xs.end())
    {
        stream << *iter;
    }
    iter++;

    for (; iter != xs.end(); iter++)
    {
        stream << ", " << *iter;
    }

    stream << "]";

    return stream;
}