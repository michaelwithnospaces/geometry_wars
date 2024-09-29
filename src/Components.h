#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "raylib.h"
#include "Vec2.h"

    class CTransform 
    {
    public:
        Vec2f pos = {0.0f, 0.0f};
        Vec2f velocity = {0.0f, 0.0f};
        float angle = 0.0f;

        CTransform(const Vec2f& p, const Vec2f& v, float a) : pos(p), velocity(v), angle(a) {};
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
    public:
        bool up =       false;
        bool down =     false;
        bool right =    false;
        bool left =     false;
        bool shoot =    false;

        CInput() {};
    };

    class CScore
    {

    };

    class CLifespan
    {

    };

#endif