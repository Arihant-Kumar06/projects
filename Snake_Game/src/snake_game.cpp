#include "snake_game.h"
SnakeGame::SnakeGame() : gameOver(false), width(50), height(50), dir(RIGHT) {
    init();
    }

    SnakeGame::~SnakeGame() {
    endwin(); 
     }


void SnakeGame::init() {
    initscr();            
    clear();
    noecho();
    cbreak();             
    curs_set(0);          
    keypad(stdscr, TRUE); 
    nodelay(stdscr, TRUE);
    srand(time(0));
    fruit.x = rand() % width;  
    fruit.y = rand() % height;
    snake.push_back(Position{ width / 2, height / 2 }); 
}

void SnakeGame::draw() {
    clear();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                mvprintw(i, j, "#"); 
            } else if (i == fruit.y && j == fruit.x) {
                mvprintw(i, j, "F");
            } else {
                bool printed = false;
                for (const auto& segment : snake) {
                    if (segment.x == j && segment.y == i) {
                        mvprintw(i, j, "O"); 
                        printed = true;
                        break;
                    }
                }
                if (!printed) {
                    mvprintw(i, j, " ");
                }
            }
        }
    }

    mvprintw(height, 0, "Score: %d", snake.size() - 1);
    refresh();
}

void SnakeGame::input() {
    int ch = getch();
    switch (ch) {
        case KEY_UP:
            if (dir != DOWN) dir = UP;
            break;
        case KEY_DOWN:
            if (dir != UP) dir = DOWN;
            break;
        case KEY_LEFT:
            if (dir != RIGHT) dir = LEFT;
            break;
        case KEY_RIGHT:
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'q':
            gameOver = true;
            break;
    }
}

void SnakeGame::logic() {
    Position newHead = snake.front();

    switch (dir) {
        case UP: newHead.y--; break;
        case DOWN: newHead.y++; break;
        case LEFT: newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }

    if (newHead.x <= 0 || newHead.x >= width - 1 || newHead.y <= 0 || newHead.y >= height - 1) {
        gameOver = true;
    }

    for (const auto& body : snake) {
        if (body.x == newHead.x && body.y == newHead.y) {
            gameOver = true;
            break;
        }
    }

    if (newHead.x == fruit.x && newHead.y == fruit.y) {
        bool fruitInSnake;
        do {
            fruitInSnake = false;
            fruit.x = rand() % width;
            fruit.y = rand() % height;
            for (const auto& body : snake) {
                if (body.x == fruit.x && body.y == fruit.y) {
                    fruitInSnake = true;
                    break;
                }
            }
        } while (fruitInSnake);
    } else {
        snake.pop_back();
    }

    snake.insert(snake.begin(), newHead);
}

void SnakeGame::run() {
    while (!gameOver) {
        draw();
        input();
        logic();
        napms(200);
    }
}
