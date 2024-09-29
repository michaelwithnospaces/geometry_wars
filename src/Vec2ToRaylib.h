#ifndef VEC2TORAYLIB_H
#define VEC2TORAYLIB_H

#include "raylib.h"
#include "Vec2.h"

template <typename T>
Vector2 toRaylibVector2(const Vec2<T>& v)
{
    return (Vector2){static_cast<float>(v.x), static_cast<float>(v.y)};
}

#endif