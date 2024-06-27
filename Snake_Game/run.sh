#!/bin/bash

# Compile the program
g++ -std=c++11 -o src/snake_game main.cpp src/snake_game.cpp -lncurses

# Run the program
./snake_game
