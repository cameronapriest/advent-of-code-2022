
/* https://adventofcode.com/2022/day/8 */
/* gcc treehouse.c -o treehouse -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_LEN 101

int determineIfTreeIsVisible(char map[99][99], int i, int j);
int calculateScenicScoreOfTree(char map[99][99], int i, int j);

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    char line[LINE_LEN];
    char map[99][99];
    int row = 0;
    int visibleTrees = 0;
    int maxScenicScore = 0;
    int scenicScore = 0;

    while (fgets(line, LINE_LEN, inputFile)) {
        for (int col = 0; col < 99; col++) {
            map[row][col] = line[col];
        }

        row++;
    }

    for (int i = 0; i < 99; i++) {
        for (int j = 0; j < 99; j++) {
            if ((i > 0 && i < 98) && (j > 0 && j < 98)) {
                visibleTrees += determineIfTreeIsVisible(map, i, j);

                scenicScore = calculateScenicScoreOfTree(map, i, j);
                if (scenicScore > maxScenicScore) {
                    maxScenicScore = scenicScore;
                }

            } else {
                visibleTrees++;
            }
        }
    }

    printf("visible trees = %d\n", visibleTrees);
    printf("max scenic score: %d\n", maxScenicScore);

    fclose(inputFile);

    return 0;
}

int determineIfTreeIsVisible(char map[99][99], int i, int j) {
    int k;

    for (k = i - 1; map[i][j] > map[k][j]; k--) { 
        if (k <= 0) {
            return 1;
        }
    }

    for (k = i + 1; map[i][j] > map[k][j]; k++) {
        if (k >= 98) {
            return 1;
        }
    }

    for (k = j - 1; map[i][j] > map[i][k]; k--) {
        if (k <= 0) {
            return 1;
        }
    }

    for (k = j + 1; map[i][j] > map[i][k]; k++) {
        if (k >= 98) {
            return 1;
        }
    }

    return 0;
}

int calculateScenicScoreOfTree(char map[99][99], int i, int j) {
    int scores[4] = {0};
    int k;

    for (k = i - 1; k >= 0; k--) {
        scores[0]++;
        if (map[i][j] <= map[k][j]) {
            break;
        }
    }

    for (k = i + 1; k <= 98; k++) {
        scores[1]++;
        if (map[i][j] <= map[k][j]) {
            break;
        }
    }

    for (k = j - 1; k >= 0; k--) {
        scores[2]++;
        if (map[i][j] <= map[i][k]) {
            break;
        }
    }

    for (k = j + 1; k <= 98; k++) {
        scores[3]++;
        if (map[i][j] <= map[i][k]) {
            break;
        }
    }

    return (scores[0] * scores[1] * scores[2] * scores[3]);
}
