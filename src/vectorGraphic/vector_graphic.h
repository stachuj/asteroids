#ifndef VECTOR_GRAPHIC_H
#define VECTOR_GRAPHIC_H

#include "raylib.h"
#include "raymath.h"

#define GFX_TERMINATOR 0.1f
extern const Vector2 gfxAsteroid1[];

void VectorGraphicDraw(Vector2* graphic, Vector2 positiion, float scale, float rotation);

#endif