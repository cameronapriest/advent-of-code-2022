
/* https://adventofcode.com/2022/day/10 */
/* gcc screen.c -o screen -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 10

void printCRT(char CRT[6][40]);
void drawPixel(int cycleNum, int regX, char CRT[6][40]);
void processClockCycle(int *cycles, int *regX, int *signalStrengths);


int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    int regX = 1;
    int cycles = 0;
    char inst[5];
    int value;
    int signalStrengths = 0;
    char CRT[6][40] = {{0}};

    while (fscanf(inputFile, "%s %d\n", inst, &value) != EOF) {
        if (strncmp(inst, "addx", 4) == 0) {
            drawPixel(cycles, regX, CRT);
            processClockCycle(&cycles, &regX, &signalStrengths);
            drawPixel(cycles, regX, CRT);
            processClockCycle(&cycles, &regX, &signalStrengths);

            regX += value;

        } else if (strncmp(inst, "noop", 4) == 0) {
            drawPixel(cycles, regX, CRT);
            processClockCycle(&cycles, &regX, &signalStrengths);
        }
    }

    printf("sum of signal strengths: %d\n\n", signalStrengths);
    printCRT(CRT);

    fclose(inputFile);

    return 0;
}

void processClockCycle(int *cycles, int *regX, int *signalStrengths) {
    (*cycles)++;
    if ((*cycles + 20) % 40 == 0) {
        *signalStrengths += (*cycles) * (*regX);
    }
}

void drawPixel(int cycleNum, int regX, char CRT[6][40]) {
    if (cycleNum % 40 == regX - 1 || cycleNum % 40 == regX || cycleNum % 40 == regX + 1) {
        CRT[(int) cycleNum / 40][cycleNum % 40] = '#';
    } else {
        CRT[(int) cycleNum / 40][cycleNum % 40] = '.';
    }
}

void printCRT(char CRT[6][40]) {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 40; col++) {
            printf("%c", CRT[row][col]);       
        }
        printf("\n");
    }
    printf("\n");
}
