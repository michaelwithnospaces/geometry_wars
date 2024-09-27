#ifndef VEC2_H
#define VEC2_H

template <typename T>
class Vec2 
{
public:
    T x;
    T y;

    Vec2();
    Vec2(T _x, T _y);
};

typedef Vec2<float> Vec2f;

#endif VEC2_H