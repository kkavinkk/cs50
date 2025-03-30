#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Maze {
    char **grid;
    int width, height;
    int playerX, playerY;
    int startX, startY;
};

struct Maze *readMaze() {
    char buffer[256];
    struct Maze *maze = malloc(sizeof(struct Maze));
    if (!maze) return NULL;
    
    maze->grid = NULL;
    maze->height = 0;
    maze->width = 0;
    int startCount = 0, goalCount = 0;

    while (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        
        maze->grid = realloc(maze->grid, (maze->height + 1) * sizeof(char *));
        maze->grid[maze->height] = strdup(buffer);
        
        if (maze->height == 0) maze->width = strlen(buffer);
        if (maze->width != strlen(buffer)) {
            free(maze);
            return NULL;
        }

        for (int i = 0; i < maze->width; i++) {
            if (buffer[i] == 'S') {
                startCount++;
                maze->startX = i;
                maze->startY = maze->height;
                maze->playerX = i;
                maze->playerY = maze->height;
            }
            if (buffer[i] == 'G') goalCount++;
        }
        maze->height++;
    }

    if (startCount != 1 || goalCount < 1) {
        free(maze);
        return NULL;
    }

    return maze;
}

struct Pos makeMove(struct Maze *maze, char direction) {
    int dx = 0, dy = 0;
    if (direction == 'n') dy = -1;
    else if (direction == 's') dy = 1;
    else if (direction == 'e') dx = 1;
    else if (direction == 'w') dx = -1;

    int newX = maze->playerX + dx;
    int newY = maze->playerY + dy;

    if (newX < 0 || newX >= maze->width || newY < 0 || newY >= maze->height || maze->grid[newY][newX] == 'X') {
        return (struct Pos){maze->playerX, maze->playerY};
    }

    while (maze->grid[newY][newX] == 'I') {
        if (newX + dx < 0 || newX + dx >= maze->width || newY + dy < 0 || newY + dy >= maze->height ||
            maze->grid[newY + dy][newX + dx] == 'X') break;
        newX += dx;
        newY += dy;
    }

    if (maze->grid[newY][newX] == 'G') {
        return (struct Pos){-1, -1};
    }

    maze->playerX = newX;
    maze->playerY = newY;
    return (struct Pos){newX, newY};
}

void reset(struct Maze *maze) {
    maze->playerX = maze->startX;
    maze->playerY = maze->startY;
}

void printMaze(struct Maze *maze) {
    for (int i = 0; i < maze->width + 2; i++) printf("=");
    printf("\n");

    for (int y = 0; y < maze->height; y++) {
        printf("|");
        for (int x = 0; x < maze->width; x++) {
            if (x == maze->playerX && y == maze->playerY) {
                printf("P");
            } else {
                printf("%c", maze->grid[y][x]);
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < maze->width + 2; i++) printf("=");
    printf("\n");
}

struct Maze *destroyMaze(struct Maze *maze) {
    if (!maze) return NULL;
    for (int i = 0; i < maze->height; i++) {
        free(maze->grid[i]);
    }
    free(maze->grid);
    free(maze);
    return NULL;
}
