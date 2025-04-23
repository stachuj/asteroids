#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"
#include "raymath.h"

typedef enum AsteroidSize {
    ASTEROID_SMALL = 1,
    ASTEROID_MEDIUM = 2,
    ASTEROID_LARGE = 4
} AsteroidSize;

#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPEED_MAX 300

#define ASTEROID_ROT_SPEED_MIN 5
#define ASTEROID_ROT_SPEED_MAX 240

#define ASTEROID_LIFETIME 10.0f

typedef struct Asteroid {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float rotationSpeed;
    float creationTime;
    AsteroidSize size;
    bool active;
} Asteroid;

Asteroid AsteroidCreate(Vector2 position, Vector2 velocity, AsteroidSize size);
void AsteroidUpdate(Asteroid* asteroid, float deltaTime, float gameTime);
void AsteroidDraw(Asteroid asteroid);

#endif