#include "../includes/cub3D.h"

double absoluteOf(double number)
{
    if (number < 0)
        return (number * (-1));
    return (number);
}

double squareOf(double number)
{
    return number * number;
}

double degToRad(double a)
{
    return (double) (a/180.00)*M_PI;
}

double FixAng(double a)
{
    if(a > 359)
        a-=360; 
    else if(a < 0)
        a+=360;
    return a;
}