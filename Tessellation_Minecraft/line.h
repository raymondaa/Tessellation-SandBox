class Line
{
public:
    double x1;
    double y1;
    double x2;
    double y2;
    double color;

    Line()
    {

    }

    Line(double x1, double y1, double x2, double y2, double color)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->color = color;
    }

    ~Line()
    {

    }

    void setX1(double newX1)
    {
        this->x1 = newX1;
    }

    void setY1(double newY1)
    {
        this->y1 = newY1;
    }

    void setX2(double newX2)
    {
        this->x2 = newX2;
    }

    void setY2(double newY2)
    {
        this->y2 = newY2;
    }
};