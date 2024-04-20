#ifndef GAME_H
#define GAME_H

void initializeGame(int rows, int cols);
void printGameMap();
void handlePlayerInput(char input);
void updateGameState();

#endif /* GAME_H */

#ifndef RANDOM_H
#define RANDOM_H

int generateRandomNumber(int min, int max);

#endif /* RANDOM_H */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "random.h"

#define BORDER_CHAR '*'
#define PLAYER_CHAR 'P'
#define FOOD_CHAR '@'
#define SNAKE_CHAR '~'

char **gameMap;
int numRows, numCols;
int playerRow, playerCol;
int snakeRow, snakeCol;
int foodRow, foodCol;

void initializeGame(int rows, int cols) {
    numRows = rows;
    numCols = cols;

    // Allocate memory for the game map
    gameMap = (char **)malloc(numRows * sizeof(char *));
    for (int i = 0; i < numRows; i++) {
        gameMap[i] = (char *)malloc(numCols * sizeof(char));
    }

    // Initialize game map with border characters
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (i == 0 || i == numRows - 1 || j == 0 || j == numCols - 1) {
                gameMap[i][j] = BORDER_CHAR;
            } else {
                gameMap[i][j] = ' ';
            }
        }
    }

    // Place player at the top left corner
    playerRow = 1;
    playerCol = 1;
    gameMap[playerRow][playerCol] = PLAYER_CHAR;

    // Place snake at the bottom right corner
    snakeRow = numRows - 2;
    snakeCol = numCols - 2;
    gameMap[snakeRow][snakeCol] = SNAKE_CHAR;

    // Generate random location for food
    generateRandomFoodLocation();
}

void generateRandomFoodLocation() {
    do {
        foodRow = generateRandomNumber(1, numRows - 2);
        foodCol = generateRandomNumber(1, numCols - 2);
    } while (foodRow == playerRow && foodCol == playerCol);
             (foodRow == snakeRow && foodCol == snakeCol);

    gameMap[foodRow][foodCol] = FOOD_CHAR;
}

#include <stdio.h>
#include "game.h"

void printGameMap() {
    // Clear the terminal screen
    printf("\033[2J\033[H");

    // Print the game map
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%c", gameMap[i][j]);
        }
        printf("\n");
    }
}


#include <stdio.h>
#include "game.h"

void handlePlayerInput(char input) {
    int newPlayerRow = playerRow;
    int newPlayerCol = playerCol;

    // Update player position based on input
    switch (input) {
        case 'w':
            newPlayerRow--;
            break;
        case 's':
            newPlayerRow++;
            break;
        case 'a':
            newPlayerCol--;
            break;
        case 'd':
            newPlayerCol++;
            break;
        default:
            // Invalid input
            printf("Invalid key\n");
            return;
    }

    // Check if the new position is valid
    if (newPlayerRow >= 1 && newPlayerRow < numRows - 1 &&
        newPlayerCol >= 1 && newPlayerCol < numCols - 1) {
        // Update player position
        gameMap[playerRow][playerCol] = ' ';
        playerRow = newPlayerRow;
        playerCol = newPlayerCol;
        gameMap[playerRow][playerCol] = PLAYER_CHAR;
    } else {
        // Invalid move, do nothing
        printf("Invalid move\n");
    }
}

#include "game.h"
#include "random.h"

void updateGameState() {
    // Move the snake randomly
    moveSnake();

    // Check if the player has collided with the snake
    if (playerRow == snakeRow && playerCol == snakeCol) {
        printf("You lose!\n");
        return;
    }

    // Check if the player has eaten the food
    if (playerRow == foodRow && playerCol == foodCol) {
        // Generate new location for food
        generateRandomFoodLocation();
    }
}

#include "game.h"
#include "random.h"

void moveSnake() {
    // Generate a random direction for the snake
    int direction = generateRandomNumber(0, 7);

    // Calculate the new position for the snake based on the direction
    int newSnakeRow = snakeRow;
    int newSnakeCol = snakeCol;

    switch (direction) {
        case 0:
            newSnakeRow--;
            break;
        case 1:
            newSnakeRow--;
            newSnakeCol++;
            break;
        case 2:
            newSnakeCol++;
            break;
        case 3:
            newSnakeRow++;
            newSnakeCol++;
            break;
        case 4:
            newSnakeRow++;
            break;
        case 5:
            newSnakeRow++;
            newSnakeCol--;
            break;
        case 6:
            newSnakeCol--;
            break;
        case 7:
            newSnakeRow--;
            newSnakeCol--;
            break;
    }

    // Check if the new position is valid
    if (newSnakeRow >= 1 && newSnakeRow < numRows - 1 &&
        newSnakeCol >= 1 && newSnakeCol < numCols - 1) {
        // Update snake position
        gameMap[snakeRow][snakeCol] = ' ';
        snakeRow = newSnakeRow;
        snakeCol = newSnakeCol;
        gameMap[snakeRow][snakeCol] = SNAKE_CHAR;
    }
}

#include "random.h"
#include <stdlib.h>
#include <time.h>

// Initialize random number generator
void initRandom() {
    srand(time(NULL));
}

int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main(int argc, char *argv[]) {
    // Check if the number of command-line arguments is correct
    if (argc != 3) {
        printf("Usage: %s <map_row> <map_col>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Check if the arguments are within the valid range
    if (rows < 5 || cols < 5) {
        printf("Map size should be at least 5x5\n");
        return 1;
    }

    // Initialize the game
    initializeGame(rows, cols);

    // Main game loop
    char input;
    while (1) {
        // Print the game map
        printGameMap();

        // Handle user input
        printf("Enter your move (w/a/s/d): ");
        scanf(" %c", &input);

        // Handle player input
        handlePlayerInput(input);

        // Update game state
        updateGameState();
    }

    return 0;
}