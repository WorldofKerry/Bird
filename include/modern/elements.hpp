class Element
{
};

class RectangularElement : Element
{
    int x0;
    int y0;
    int x1;
    int y1;

public:
    int width();
    int height();

    bool collides(int, int);
};