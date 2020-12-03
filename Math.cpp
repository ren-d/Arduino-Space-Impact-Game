#include "Math.h"
#include <cmath>
int Math::Clamp(int value, int min, int max)
{
    if(value > max)
    {
        return max;
    }
    else if(value < min)
    {
        return min;
    }
    else
    {
        return value;
    }
}

float Math::SQRT(int value)
{
    return sqrt(value);
}



