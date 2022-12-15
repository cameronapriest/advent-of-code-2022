
/* https://adventofcode.com/2022/day/14 */
/* gcc reservoir.c -o reservoir -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 250

/* example */
#define X_MIN 494
#define X_MAX 503
#define Y_MAX 9

// #define X_MIN 492 //494
// #define X_MAX 562 //503
#define X_SIZE (X_MAX - X_MIN + 1)
#define Y_MIN 0
// #define Y_MAX 173 //9
#define Y_SIZE (Y_MAX - Y_MIN + 1)
#define X_OFFSET X_MIN

typedef struct {
    int x;  /* distance to the right */
    int y;  /* distance down */
} coord;

void drawPath(coord curr, coord prev, char drawing[Y_SIZE][X_SIZE]);
void drawCave(coord sandOrigin, char drawing[Y_SIZE][X_SIZE]);
void findDomainAndRange(int *xMin, int *xMax, int *yMin, int *yMax, coord curr);


int main(void) {
    FILE *input = fopen("example.txt", "r");
    char line[LINE_SIZE];
    char *token;
    coord curr, prev, sandOrigin;
    int i = 0;
    //int j = 0;
    //int xMin = 0, xMax = 0, yMin = 0, yMax = 0;
    char drawing[Y_SIZE][X_SIZE];

    sandOrigin.x = 500 - X_MIN;
    sandOrigin.y = 0;


    while (fgets(line, LINE_SIZE, input)) {
        printf("%s", line);

        token = strtok(line, " -> ");
        while (token) {
            curr.x = atoi(token);
            curr.y = atoi(&token[4]);
            printf("\t(%d, %d)\n", curr.x, curr.y);

            if (i > 0) {
                drawPath(curr, prev, drawing);
            }
            
            /* if (j == 0) {
                xMin = curr.x;
                xMax = curr.x;
                yMin = curr.y;
                yMax = curr.y;
                j++;
            } else {
                findDomainAndRange(&xMin, &xMax, &yMin, &yMax, curr);
            } */

            prev.x = curr.x;
            prev.y = curr.y;
            i++;

            token = strtok(NULL, " -> \n");
        }

        i = 0;

        printf("-----------------------\n");
    }

    drawCave(sandOrigin, drawing);

    int unit = 1;
    int row = 0;

    while (1) {
        row = sandOrigin.y;
        while (drawing[row + 1][sandOrigin.x] != '#' && drawing[row + 1][sandOrigin.x] != 'o') {
            row++;
        }

        /* if (drawing[row + 1][sandOrigin.x - 1] != '#' && drawing[row + 1][sandOrigin.x - 1] != 'o') {
            drawing[row + 1][sandOrigin.x - 1] = 'o';
        } else if (drawing[row + 1][sandOrigin.x + 1] != '#' && drawing[row + 1][sandOrigin.x + 1] != 'o') {
            drawing[row + 1][sandOrigin.x + 1] = 'o';
        } */

        drawing[row][sandOrigin.x] = 'o';
        drawCave(sandOrigin, drawing);
        unit++;
    }

    //printf("x: %d to %d\ny: %d to %d\n", xMin, xMax, yMin, yMax);

    return 0;
}

void drawPath(coord curr, coord prev, char drawing[Y_SIZE][X_SIZE]) {
    printf("\t  drawing path from (%d, %d) to (%d, %d)\n", prev.x, prev.y, curr.x, curr.y);

    if (curr.x == prev.x) {
        if (curr.y > prev.y) {
            for (int row = prev.y; row <= curr.y; row++) {
                drawing[row][curr.x - X_OFFSET] = '#';
            }
        } else if (curr.y < prev.y) {
            for (int row = curr.y; row <= prev.y; row++) {
                drawing[row][curr.x - X_OFFSET] = '#';
            }
        }
    }
    
    if (curr.y == prev.y) {
        if (curr.x > prev.x) {
            for (int col = prev.x; col <= curr.x; col++) {
                drawing[curr.y][col - X_OFFSET] = '#';
            }
        } else if (curr.x < prev.x) {
            for (int col = curr.x; col <= prev.x; col++) {
                drawing[curr.y][col - X_OFFSET] = '#';
            }
        }
    }
}

void drawCave(coord sandOrigin, char drawing[Y_SIZE][X_SIZE]) {
    printf("\n");
    for (int y = 0; y < Y_SIZE; y++) {
        for (int x = 0; x < X_SIZE; x++) {
            if (drawing[y][x] == '#') {
                printf("#");
            } else if (x == sandOrigin.x && y == sandOrigin.y) {
                printf("+");
            } else if (drawing[y][x] == 'o') {
                printf("o");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void findDomainAndRange(int *xMin, int *xMax, int *yMin, int *yMax, coord curr) {
    if (curr.x < *xMin) {
        *xMin = curr.x;
    } else if (curr.x > *xMax) {
        *xMax = curr.x;
    }

    if (curr.y < *yMin) {
        *yMin = curr.y;
    } else if (curr.y > *yMax) {
        *yMax = curr.y;
    }
}
