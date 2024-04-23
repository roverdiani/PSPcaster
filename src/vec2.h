#ifndef VEC2_H
#define VEC2_H

class vec2
{
public:
    vec2() = default;
    vec2(float newX, float newY)
    {
        x = newX;
        y = newY;
    }

    vec2& operator+=(const vec2 &v)
    {
        x += v.x;
        y += v.y;

        return *this; 
    }

    float x;
    float y;
};

#endif
