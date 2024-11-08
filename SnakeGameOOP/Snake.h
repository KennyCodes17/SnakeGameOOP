#pragma once
#include "raylib.h"
#include <vector>
#include <deque>


//colors
extern Color green;
extern Color darkGreen;

extern int cellSize;
extern int cellCount;
extern int offSet;


//game functions;
bool eventTriggered(double interval);
bool checkElementsInDeque(Vector2 element, std::deque<Vector2> deque);

//apple class
class Apple
{
public:
    // Apple Constructor
    Apple(std::deque<Vector2> snakeBody);
    // Apple Destructor
    ~Apple();

    //draw method
    void Draw();

    //generate random position method
    Vector2 generateRandomCell();
    Vector2 generateRandomPos(std::deque<Vector2> snakeBody);
    Vector2 getPosition();
    void setPosition(std::deque<Vector2> snakeBody);

private:
    Texture2D appleTexture;

    Vector2 position;
};

//snake class
class Snake
{
public:

    std::deque<Vector2> snakeBody = {{10, 10},{9, 10},{8, 10}};
    Vector2 direction = { 1, 0 };
    bool addSegment = false;
    void Draw();
    void Update();
    void changeSnakeDirection();

private:

};

class Game
{
public:
    Snake snake = Snake();
    Apple apple = Apple(snake.snakeBody);
    bool isGameOver = false;


    void Draw();
    void Update();
    void appleCollision();
    void checkWallCollision();
    void checkSelfCollision();
    void splashScreen();
    void GameOver();


private:
    Texture2D snakeScreen;

};
