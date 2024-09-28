#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "raylib.h"
#include "Vec2.h"

    class CTransform 
    {

    };

    class CShape
    {
    public:
        Vec2f center;
        float r;
        int sides;
        Color color;

        CShape() : center({0.0f, 0.0f}), sides(3), r(1.0f), color({255, 255, 255, 255}) {};
        CShape(Vec2f _center, int _sides, float _r, Color _color) : center(_center), sides(_sides), r(_r), color(_color) {};
    };

    class CCollision
    {

    };

    class CInput
    {

    };

    class CScore
    {

    };

    class CLifespan
    {

    };

#endif