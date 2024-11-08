#include "Snake.h"
#include <raymath.h>
#include <iostream>

//colors
Color green = { 173, 204, 96, 255 };
Color darkGreen = { 43, 51, 24, 255 };

int cellSize = 30;
int cellCount = 25;
int offSet = 75;


double lastUpdateTime = 0;

//game functions
bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool checkElementsInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}

//Apple constructor
Apple:: Apple(std::deque<Vector2> snakeBody)
{
    //load apple image to game
    Image appleImage = LoadImage("C:/Users/kenny/OneDrive/Documents/VS projects/SnakeGameOOP/SnakeGameOOP/Graphics/apple_snake_game.png");
    //load apple texture to game
    appleTexture = LoadTextureFromImage(appleImage);
    //unload image to free up memory
    UnloadImage(appleImage);

    position = generateRandomPos(snakeBody);
}
Apple:: ~Apple()
{
    UnloadTexture(appleTexture);
}
// AppleMethods
void Apple::Draw()
{
    DrawTexture(appleTexture, offSet + position.x * cellSize, offSet + position.y * cellSize, WHITE);
}

Vector2 Apple::generateRandomCell()
{
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return Vector2{ x,y };
}

Vector2 Apple::generateRandomPos(std::deque<Vector2> snakeBody)
{
    Vector2 position = generateRandomCell();
    while (checkElementsInDeque(position, snakeBody))
    {
        position = generateRandomCell();
    }
    return position;
}

Vector2 Apple::getPosition()
{
    return position;
}

void Apple::setPosition(std::deque<Vector2> snakeBody)
{
    position = generateRandomPos(snakeBody);
}

//Snake methods
void Snake :: Draw()
{
    for (int i = 0; i < snakeBody.size(); i++)
    {
        float x = snakeBody[i].x;
        float y = snakeBody[i].y;
        Rectangle snakeSegment = Rectangle{ offSet + x * cellSize, offSet + y * cellSize, (float)cellSize, (float)cellSize };
        DrawRectangleRounded(snakeSegment, 0.75, 6, darkGreen);
    }
}

void Snake::Update()
{
    snakeBody.push_front(Vector2Add(snakeBody[0], direction));

    if (addSegment == true)
    {
        addSegment = false;
    }
    else
    {
        snakeBody.pop_back();
    }
}

void Snake::changeSnakeDirection()
{
    //check for key being pressed
    //UP
    if (IsKeyPressed(KEY_W) && direction.y != 1)
    {
        direction = { 0 , -1 };
    }
    //Down
    if (IsKeyPressed(KEY_S) && direction.y != -1)
    {
        direction = { 0, 1 };
    }
    //Right 
    if (IsKeyPressed(KEY_D) && direction.x != -1)
    {
        direction = { 1 , 0 };
    }
    //Left
    if (IsKeyPressed(KEY_A) && direction.x != 1)
    {
        direction = { -1, 0 };
    }
}

//Game Methods
void Game::Draw()
{
    apple.Draw();
    snake.Draw();
}

void Game::Update()
{
    if (!isGameOver)
    {
        snake.Update();
        appleCollision();
        checkWallCollision();
        checkSelfCollision();
    }
}

void Game::appleCollision()
{
    if (Vector2Equals(snake.snakeBody[0], apple.getPosition()))
    {
        apple.setPosition(snake.snakeBody);
        std::cout << "apple eaten";
        snake.addSegment = true; 
    }
}

void Game::GameOver()
{
    isGameOver = true;
    std::cout << "Game Over"<<std::endl;
}

void Game::checkSelfCollision()
{
    Vector2 headPosition = snake.snakeBody[0];  // Head position

    for (int i = 1; i < snake.snakeBody.size(); i++)
    {
        if (Vector2Equals(snake.snakeBody[i], headPosition))
        {
            GameOver();  
            return;
        }
    }
}

void Game::checkWallCollision()
{
    if (snake.snakeBody[0].x == cellCount || snake.snakeBody[0].x == -1)
    {
        GameOver();
    }
    if (snake.snakeBody[0].y == cellCount || snake.snakeBody[0].y == -1)
    {
        GameOver();
    }
}
