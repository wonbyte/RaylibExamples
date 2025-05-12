#include <stdlib.h>

#include "raylib.h"

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "'raylib' [core] example - keyboard input");

    Vector2 ball_position = {(float)screen_width / 2, (float)screen_height / 2};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
            ball_position.x += 2.0F;
        if (IsKeyDown(KEY_LEFT))
            ball_position.x -= 2.0F;
        if (IsKeyDown(KEY_UP))
            ball_position.y -= 2.0F;
        if (IsKeyDown(KEY_DOWN))
            ball_position.y += 2.0F;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
        DrawCircleV(ball_position, 50, MAROON);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}