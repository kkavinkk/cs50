#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

struct Maze {
    char **tiles;
    int width;
    int height;
    struct Pos start;
    struct Pos current;
};

// Helper to check if a character is a digit ('0'–'9')
int isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Helper to copy a line
char *copyLine(const char *src, int len) {
    char *line = malloc(len + 1);
    strncpy(line, src, len);
    line[len] = '\0';
    return line;
}

// Read maze
struct Maze *readMaze() {
    int capacity = 8;
    int height = 0;
    int width = -1;
    char **rows = malloc(capacity * sizeof(char *));
    if (!rows) return NULL;

    char buffer[1024];
    int startCount = 0, goalCount = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (buffer[0] == '\n') break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') buffer[--len] = '\0';

        if (width == -1) width = len;
        if (len != width) {
            for (int i = 0; i < height; i++) free(rows[i]);
            free(rows);
            return NULL;
        }

        if (height >= capacity) {
            capacity *= 2;
            char **temp = realloc(rows, capacity * sizeof(char *));
            if (!temp) {
                for (int i = 0; i < height; i++) free(rows[i]);
                free(rows);
                return NULL;
            }
            rows = temp;
        }

        rows[height] = copyLine(buffer, len);
        for (int i = 0; i < len; i++) {
            if (buffer[i] == 'S') startCount++;
            if (buffer[i] == 'G') goalCount++;
        }
        height++;
    }

    if (startCount != 1 || goalCount < 1) {
        for (int i = 0; i < height; i++) free(rows[i]);
        free(rows);
        return NULL;
    }

    struct Maze *m = malloc(sizeof(struct Maze));
    m->width = width;
    m->height = height;
    m->tiles = rows;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (rows[y][x] == 'S') {
                m->start.x = x;
                m->start.y = y;
                m->current = m->start;
                break;
            }
        }
    }

    return m;
}

// Teleport
void teleport(struct Maze *m) {
    char digit = m->tiles[m->current.y][m->current.x];
    for (int y = 0; y < m->height; y++) {
        for (int x = 0; x < m->width; x++) {
            if (x == m->current.x && y == m->current.y) continue;
            if (m->tiles[y][x] == digit) {
                m->current.x = x;
                m->current.y = y;
                return;
            }
        }
    }
}

// Make a move
struct Pos makeMove(struct Maze *m, char dir) {
    int dx = 0, dy = 0;
    if (dir == 'n') dy = -1;
    else if (dir == 's') dy = 1;
    else if (dir == 'e') dx = 1;
    else if (dir == 'w') dx = -1;

    int nx = m->current.x + dx;
    int ny = m->current.y + dy;

    if (nx < 0 || ny < 0 || nx >= m->width || ny >= m->height) {
        return m->current;
    }

    char next = m->tiles[ny][nx];
    if (next == 'X') return m->current;

    m->current.x = nx;
    m->current.y = ny;

    // Slide on ice
    while (m->tiles[m->current.y][m->current.x] == 'I') {
        int tx = m->current.x + dx;
        int ty = m->current.y + dy;
        if (tx < 0 || ty < 0 || tx >= m->width || ty >= m->height) break;
        if (m->tiles[ty][tx] == 'X') break;
        m->current.x = tx;
        m->current.y = ty;
    }

    // Teleport
    if (isDigit(m->tiles[m->current.y][m->current.x])) {
        teleport(m);
    }

    // Win
    if (m->tiles[m->current.y][m->current.x] == 'G') {
        struct Pos win = { -1, -1 };
        return win;
    }

    return m->current;
}

// Reset player
void reset(struct Maze *m) {
    m->current = m->start;
}

// Print maze
void printMaze(struct Maze *m) {
    for (int i = 0; i < m->width + 2; i++) putchar('-');
    putchar('\n');

    for (int y = 0; y < m->height; y++) {
        putchar('|');
        for (int x = 0; x < m->width; x++) {
            if (m->current.x == x && m->current.y == y) {
                putchar('P');
            } else {
                putchar(m->tiles[y][x]);
            }
        }
        putchar('|');
        putchar('\n');
    }

    for (int i = 0; i < m->width + 2; i++) putchar('-');
    putchar('\n');
}

// Free all memory
struct Maze *destroyMaze(struct Maze *m) {
    if (!m) return NULL;
    for (int i = 0; i < m->height; i++) {
        free(m->tiles[i]);
    }
    free(m->tiles);
    free(m);
    printf("Error, your destroyMaze doesn't return NULL\n");
    return NULL;
}
