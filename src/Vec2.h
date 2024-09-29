#ifndef VEC2_H
#define VEC2_H

#include <cmath>

template <typename T>
class Vec2 
{
public:
    T x;
    T y;

    Vec2();
    Vec2(T _x, T _y);

    bool operator == (const Vec2& rhs) const;
    bool operator != (const Vec2& rhs) const;

    Vec2 operator + (const Vec2& rhs) const;
    Vec2 operator - (const Vec2& rhs) const;
    Vec2 operator / (const T& val) const;
    Vec2 operator * (const T& val) const;

    void operator += (const Vec2& rhs);
    void operator -= (const Vec2& rhs);
    void operator *= (const T& val);
    void operator /= (const T& val);

    float dist(const Vec2& rhs) const;
    void norm();
};

typedef Vec2<float> Vec2f;

template <typename T>
Vec2<T>::Vec2() : x(0), y(0) {};

template <typename T>
Vec2<T>::Vec2(T _x, T _y) : x(_x), y(_y) {};

template <typename T>
bool Vec2<T>::operator == (const Vec2& rhs) const 
{
    return (this->x == rhs.x && this->y == rhs.y);
}

template <typename T>
bool Vec2<T>::operator != (const Vec2& rhs) const
{
    return (this->x != rhs.x && this->y != rhs.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator + (const Vec2& rhs) const
{
    Vec2<T> n;
    n.x = this->x + rhs.x;
    n.y = this->y + rhs.y;
    return n;
}

template <typename T>
Vec2<T> Vec2<T>::operator - (const Vec2& rhs) const
{
    Vec2<T> n;
    n.x = this->x - rhs.x;
    n.y = this->y - rhs.y;
    return n;
}

template <typename T>
Vec2<T> Vec2<T>::operator / (const T& val) const
{
    Vec2<T> n;
    n.x = this->x / val;
    n.y = this->y / val;
    return n;
}

template <typename T>
Vec2<T> Vec2<T>::operator * (const T& val) const
{
    Vec2<T> n;
    n.x = this->x * val;
    n.y = this->y * val;
    return n;
}

template <typename T>
void Vec2<T>::operator += (const Vec2& rhs)
{
    this->x = this->x + rhs.x;
    this->y = this->y + rhs.y;
}

template <typename T>
void Vec2<T>::operator -= (const Vec2& rhs)
{
    this->x = this->x - rhs.x;
    this->y = this->y - rhs.y;
}

template <typename T>
void Vec2<T>::operator *= (const T& val)
{
    this->x = this->x * val;
    this->y = this->y * val;
}

template <typename T>
void Vec2<T>::operator /= (const T& val)
{
    this->x = this->x / val;
    this->y = this->y / val;
}

template <typename T>
float Vec2<T>::dist(const Vec2& rhs) const
{   
    float dx = this->x - rhs.x;
    float dy = this->y - rhs.y;

    return sqrt(dx * dx + dy * dy);
}

template <typename T>
void Vec2<T>::norm()
{
    float length = sqrt(x * x + y * y);
    if (length != 0) 
    {
        this->x /= length;
        this->y /= length;
    }
}

#endif