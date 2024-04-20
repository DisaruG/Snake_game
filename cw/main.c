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
