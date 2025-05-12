#include <stdlib.h>

#include "raylib.h"

int main(void)
{
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "raylib [core] example - mouse input");

    Color ball_color = DARKBLUE;
    int is_cursor_hidden = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_H))
        {
            if (is_cursor_hidden == 0)
            {
                HideCursor();
                is_cursor_hidden = 1;
            }
            else
            {
                ShowCursor();
                is_cursor_hidden = 0;
            }
        }

        const Vector2 ball_position = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            ball_color = MAROON;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
            ball_color = LIME;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            ball_color = DARKBLUE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE))
            ball_color = PURPLE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA))
            ball_color = YELLOW;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD))
            ball_color = ORANGE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_BACK))
            ball_color = BEIGE;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ball_position, 40, ball_color);

        DrawText("move ball with mouse and click mouse button to change color", 10, 10, 20,
                 DARKGRAY);
        DrawText("Press 'H' to toggle cursor visibility", 10, 30, 20, DARKGRAY);

        if (is_cursor_hidden == 1)
            DrawText("CURSOR HIDDEN", 20, 60, 20, RED);
        else
            DrawText("CURSOR VISIBLE", 20, 60, 20, LIME);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}