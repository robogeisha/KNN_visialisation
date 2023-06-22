// Written by Esra Genc on 22.06.23


#include "raylib.h"
#include <stdbool.h>
#include <math.h>

#define MAX_SPOTS 100

typedef struct {
    Vector2 position;
    bool isSafe;
    Color color;
} Spot;

Spot spots[MAX_SPOTS];
Color colorScheme[2];

Color generateOppositeColor(Color color) {
    int r = 255 - color.r;
    int g = 255 - color.g;
    int b = 255 - color.b;

    return (Color){ r, g, b, 255 };
}

void generateColorScheme() {
    int r = GetRandomValue(0, 255);
    int g = GetRandomValue(0, 255);
    int b = GetRandomValue(0, 255);
    colorScheme[0] = (Color){ r, g, b, 255 };

    colorScheme[1] = generateOppositeColor(colorScheme[0]);
}

void generateNewSpots() {
    for (int i = 0; i < MAX_SPOTS; i++) {
        spots[i].position = (Vector2){ GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight()) };
        spots[i].color = colorScheme[0];
    }
}

bool predictSpotSafety(Vector2 position) {
    int neighborCount = 0;

    for (int i = 0; i < MAX_SPOTS; i++) {
        float dx = position.x - spots[i].position.x;
        float dy = position.y - spots[i].position.y;
        float distance = sqrtf(dx * dx + dy * dy);

        if (distance < 50) {
            spots[i].color = colorScheme[1];
            neighborCount++;
        } else {
            spots[i].color = colorScheme[0];
        }
    }

    return neighborCount < (MAX_SPOTS - neighborCount);
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "KNN Visualizer");
    SetTargetFPS(60);

    Vector2 mousePosition = GetMousePosition();  // Get the initial mouse position

    generateColorScheme();
    generateNewSpots();

    while (!WindowShouldClose()) {
        mousePosition = GetMousePosition();  // Update the mouse position

        if (IsKeyPressed(KEY_G)) {
            generateColorScheme();
            generateNewSpots();
        }

        bool isSafe = predictSpotSafety(mousePosition);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < MAX_SPOTS; i++) {
            DrawCircleV(spots[i].position, 10, spots[i].color);
        }

        DrawCircleV(mousePosition, 10, generateOppositeColor(isSafe ? colorScheme[0] : colorScheme[1]));
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
