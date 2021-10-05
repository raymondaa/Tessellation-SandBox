#include <stdio.h>
#include <iostream>

class Triangle
{
public:
    double Ax;
    double Ay;
    double Bx;
    double By;
    double Cx;
    double Cy;

    Triangle()
    {

    }

    Triangle(double Ax, double Ay, double Bx, double By, double Cx, double Cy)
    {
        this->Ax = Ax;
        this->Ay = Ay;
        this->Bx = Bx;
        this->By = By;
        this->Cx = Cx;
        this->Cy = Cy;
    }


    ~Triangle()
    {

    }

    void setAx(double newAx)
    {
        this->Ax = newAx;
    }

    void setBx(double newBx)
    {
        this->Bx = newBx;
    }

    void setCx(double newCx)
    {
        this->Cx = newCx;
    }

    void setAy(double newAy)
    {
        this->Ay = newAy;
    }

    void setBy(double newBy)
    {
        this->By = newBy;
    }

    void setCy(double newCy)
    {
        this->Cy = newCy;
    }
};
