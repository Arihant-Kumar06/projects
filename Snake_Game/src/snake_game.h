#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
enum Direction { UP, DOWN, LEFT, RIGHT };
struct Position {
    int x, y;
};
class SnakeGame {
    private:
    void init();
    void draw();
    void input();
    void logic();

    bool gameOver;
    int width, height;
    Direction dir;
    Position fruit;
    vector<Position> snake;

    public:
    SnakeGame();
    ~SnakeGame();
    void run();
   
};
#endif