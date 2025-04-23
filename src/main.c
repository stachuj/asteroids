#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#include "asteroid.h"

#define WINDOW_W 1024
#define WINDOW_H 768
const Vector2 windowCenter = {WINDOW_W/2, WINDOW_H/2};

#define MAX_ASTEROIDS 64
#define ASTEROID_RANDOM_ANGLE 30
#define ASTEROID_DELAY 0.25f

static AsteroidSize _sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM, ASTEROID_LARGE};
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1.0f;

#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

void UpdateDrawFrame(void);
void AddAsteroid(Vector2 position, AsteroidSize size);
Vector2 GetNextAsteroidPosition();

int main() {

    srand(time(0));

    InitWindow(WINDOW_W, WINDOW_H, "ASTEROIDS");

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}

void UpdateDrawFrame(void) {

    float deltaTime = GetFrameTime();
    float gameTime = (float)GetTime();

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        AsteroidUpdate(_asteroids + i, deltaTime, gameTime);
    }

    if (gameTime > _lastAsteroidCreationTime + ASTEROID_DELAY) {
        AddAsteroid(GetNextAsteroidPosition(), _sizes[GetRandomValue(0,2)]);
        _lastAsteroidCreationTime = gameTime;
    }

    BeginDrawing();

        ClearBackground(NEARBLACK);

        for (int i = 0; i < MAX_ASTEROIDS; i++) {
            AsteroidDraw(_asteroids[i]);
        }

    EndDrawing();

}

void AddAsteroid(Vector2 position, AsteroidSize size) {

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (_asteroids[i].active)
            continue;

        Vector2 velocity = Vector2Subtract(windowCenter, position);
        velocity = Vector2Scale(Vector2Normalize(velocity), (float)GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX));
        velocity = Vector2Rotate(velocity, (float)GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE) * DEG2RAD);

        _asteroids[i] = AsteroidCreate(position, velocity, size);
        return;
    }

     TraceLog(LOG_ERROR, "Failed to create asteroid, not enough room!");
}

Vector2 GetNextAsteroidPosition() {
    int padding = 128;
    Vector2 position = {-padding, -padding};

    // spawn off horizontal edge
    if (GetRandomValue(0, 1)) {

        position.x += GetRandomValue(0, 1) * (WINDOW_W + 2 * padding);
        position.y = GetRandomValue(-padding, WINDOW_H + padding);

    }
    //spawn off vertical edge
    else {
        position.x = GetRandomValue(-padding, WINDOW_W + padding);
        position.y += GetRandomValue(0, 1) * (WINDOW_H + 2 * padding);
    }

    return position;
}