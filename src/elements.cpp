#include <algorithm>

#include "elements.hpp"

int RectangularElement::width()
{
    return std::abs(x1 - x0);
}

int RectangularElement::height()
{
    return std::abs(y1 - y0);
}

bool RectangularElement::collides(int x, int y)
{
    return (x <= std::max(x0, x1) && y >= std::min(x0, x1) && (y <= std::max(y0, y1) && y >= std::min(y0, y1)));
}