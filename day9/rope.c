
/* https://adventofcode.com/2022/day/9 */
/* gcc rope.c -o rope -Wall -Wpedantic -Wextra */
/* ulimit -s 16384 */ /* increase stack size */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_LEN 101
#define SIZE_SIDE 1000
#define MIDPOINT SIZE_SIDE / 2

typedef struct {
    int row;
    int col;
} coord;

void movePair(char direction, int *headCol, int *headRow, int *tailCol, int *tailRow);
void markPosition(uint8_t positionsTailVisited[SIZE_SIDE][SIZE_SIDE], int row, int col);
void printRope(coord rope[10]);


int main(void) {
    FILE *inputFile = fopen("input-2.txt", "r");

    uint8_t positionsTailVisited[SIZE_SIDE][SIZE_SIDE] = {{0}};
    char direction;
    int steps;
    int visited = 0;

    int headCol = 0;
    int headRow = 0;
    int tailCol = 0;
    int tailRow = 0;

    coord rope[10];

    for (int i = 0; i < 10; i++) {
        rope[i].row = 0;
        rope[i].col = 0;
    }

    /* ---------- part 1 ---------- */

    /* while (fscanf(inputFile, "%c %d\n", &direction, &steps) != EOF) {
        printf("[%c] [%d]\n", direction, steps);

        for (int i = 0; i < steps; i++) {
            movePair(direction, &headCol, &headRow, &tailCol, &tailRow);
            markPosition(positionsTailVisited, tailRow, tailCol);
            
            if (tailRow + MIDPOINT < 0 || tailCol + MIDPOINT < 0 || headRow + MIDPOINT < 0 || headCol + MIDPOINT < 0) {
                exit(1);
            }
        }
    }

    for (int i = 0; i < SIZE_SIDE; i++) {
        for (int j = 0; j < SIZE_SIDE; j++) {
            if (positionsTailVisited[i][j] == 1) {
                visited++;
            }
        }
    }

    printf("%d visited\n", visited); */

    /* ---------- part 2 ---------- */

    while (fscanf(inputFile, "%c %d\n", &direction, &steps) != EOF) {
        printf("[%c] [%d]\n", direction, steps);

        for (int i = 0; i < steps; i++) {
            for (int j = 0; j < 9; j++) {
                movePair(direction, &(rope[j].col), &(rope[j].row), &(rope[j + 1].col), &(rope[j + 1].row));
                printRope(rope);
            }

            markPosition(positionsTailVisited, rope[9].row, rope[9].col);
            
            if (tailRow + MIDPOINT < 0 || tailCol + MIDPOINT < 0 || headRow + MIDPOINT < 0 || headCol + MIDPOINT < 0) {
                exit(1);
            }
        }
    }

    for (int i = 0; i < SIZE_SIDE; i++) {
        for (int j = 0; j < SIZE_SIDE; j++) {
            if (positionsTailVisited[i][j] == 1) {
                visited++;
            }
        }
    }

    printf("%d visited\n", visited);

    fclose(inputFile);

    return 0;
}

void movePair(char direction, int *headCol, int *headRow, int *tailCol, int *tailRow) {
    if (direction == 'R') { /* right */
        (*headCol)++;

        if (*headCol - *tailCol > 1) {
            (*tailCol)++;

            if (*tailRow != *headRow) {
                *tailRow = *headRow;
            }
        }                
    }

    else if (direction == 'L') { /* left */
        (*headCol)--;

        if (*tailCol - *headCol > 1) {
            (*tailCol)--;

            if (*tailRow != *headRow) {
                *tailRow = *headRow;
            }
        }
    }

    else if (direction == 'U') { /* up */
        (*headRow)++;

        if (*headRow - *tailRow > 1) {
            (*tailRow)++;

            if (*tailCol != *headCol) {
                *tailCol = *headCol;
            }
        }
    }

    else if (direction == 'D') { /* down */
        (*headRow)--;

        if (*tailRow - *headRow > 1) {
            (*tailRow)--;

            if (*tailCol != *headCol) {
                *tailCol = *headCol;
            }
        }
    }
}

void markPosition(uint8_t positionsTailVisited[SIZE_SIDE][SIZE_SIDE], int row, int col) {
    if (positionsTailVisited[row + MIDPOINT][col + MIDPOINT] == 0) {
        positionsTailVisited[row + MIDPOINT][col + MIDPOINT] = 1;
    }
}

void printRope(coord rope[10]) {
    printf("\n\t");
    for (int i = 0; i < 10; i++) {
        printf("%d ", rope[i].row);
    }
    printf("]\n\t");
    for (int i = 0; i < 10; i++) {
        printf("%d ", rope[i].col);
    }
    printf("]\n");
}
