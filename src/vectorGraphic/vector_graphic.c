#include "vector_graphic.h"

static Vector2 gfxTerminator = {GFX_TERMINATOR};
const Vector2 gfxAsteroid1[] = {
    {0, 4},
    {4, 8},
    {8, 4},
    {8, 0},
    {8, -4},
    {2, -8},
    {-4, -8},
    {-8, -4},
    {-8, 4},
    {-4, 8},
    {0, 4},
    {GFX_TERMINATOR}
};

void VectorGraphicDraw(Vector2* gr, Vector2 position, float scale, float rotation) {

    Vector2 pointA;
    Vector2 pointB;

    bool left_intersect = false;
    bool right_intersect = false;

    unsigned i = 0;

    Vector2* graphic = gfxAsteroid1;

    pointA = graphic[i];
    pointA = Vector2Add(position, Vector2Scale(Vector2Rotate(pointA, rotation), scale));

    while(!Vector2Equals(graphic[i+1], gfxTerminator)) {

        pointB = graphic[i+1];
        pointB = Vector2Add(position, Vector2Scale(Vector2Rotate(pointB, rotation), scale));

        DrawLineV(pointA, pointB, WHITE);

        if (pointA.x < 1024 && pointB.x > 1024) {
            right_intersect = true;
        }
        else if (pointA.x < 0 && pointB.x > 0) {
            left_intersect = true;
        }

        pointA = pointB;
        i++;
    }

    Vector2 sub = {1024, 0};

    if (right_intersect)
        VectorGraphicDraw(gfxAsteroid1, Vector2Subtract(position, sub), scale, rotation);

}