#include "Snake.h"
#include <iostream>
#include <conio.h> 
#include "raylib.h"

int main()
{
    InitWindow(2* offSet + cellSize * cellCount, 2* offSet + cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);

    //variables
    Game game;

    //game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
       
        ClearBackground(green);

        if (!game.isGameOver)
        {
            if (eventTriggered(0.2))
            {
                game.Update();
            }

            game.snake.changeSnakeDirection();
            DrawRectangleLinesEx(Rectangle{ (float)offSet - 5, (float)offSet - 5, (float)cellSize * cellCount + 10 , (float)cellSize * cellCount + 10 }, 5, darkGreen);
            DrawText("Snake Game", offSet - 5, 20, 40, darkGreen);
            game.Draw();
        }
        else
        {
            DrawText("Game Over! Press R to Restart", 200, 375, 20, RED);
            if (IsKeyPressed(KEY_R))  // Optional restart option
            {
                game = Game();  // Reset the game by reinitializing
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}