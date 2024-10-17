#include "Snake.h"
#include "GameLogic.cpp" 
#include <iostream>
#include <conio.h> 
#include "raylib.h"

int main()
{

    InitWindow(750, 750, " Snake Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
