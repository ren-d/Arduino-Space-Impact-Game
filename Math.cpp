#include "Math.h"
#include <cmath>

//clamps a value to a certain bounds
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

//square roots
float Math::SQRT(int value)
{
    return sqrt(value);
}



