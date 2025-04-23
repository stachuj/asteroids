#include "asteroid.h"

Asteroid AsteroidCreate(Vector2 position, Vector2 velocity, AsteroidSize size) {
    return (Asteroid) {
        .position = position,
        .velocity = velocity,
        .rotation = GetRandomValue(0, 360),
        .rotationSpeed = GetRandomValue(ASTEROID_ROT_SPEED_MIN, ASTEROID_ROT_SPEED_MAX),
        .creationTime = (float)GetTime(),
        .size = size,
        .active = true
    };
}

void AsteroidUpdate(Asteroid* asteroid, float deltaTime, float gameTime) {
    if (gameTime > asteroid->creationTime + ASTEROID_LIFETIME)
        asteroid->active = false;
    
    if (!asteroid->active)
        return;

    asteroid->position = Vector2Add(asteroid->position, Vector2Scale(asteroid->velocity, deltaTime));
    asteroid->rotation += (asteroid->rotationSpeed * deltaTime);
}

void AsteroidDraw(Asteroid asteroid) {
    Color drawColor = WHITE;
    if (!asteroid.active)
        drawColor = RED;

    DrawPolyLines(asteroid.position, 3, asteroid.size * 16.0f, asteroid.rotation, drawColor);
    //DrawLineV(asteroid.position, Vector2Add(asteroid.position, asteroid.velocity), RED);
}