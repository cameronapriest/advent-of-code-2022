
/* https://adventofcode.com/2022/day/1 */
/* gcc calories.c -o calories -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BYTES_PER_LINE 10

int findMaxCalories(FILE *inputFile);           /* part 1 */
int findTopThreeMaxCalories(FILE *inputFile);   /* part 2 */
void siftThroughTopThreeElfCalories(int *maxCalories, int currentElfCalories);
int compare(const void *a, const void *b);


int main(void) {
    FILE *inputFile;
    char *filename = "input.txt";

    inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("error: file %s not found\n", filename);
        exit(1);
    }

    printf("Part 1: max calories = %d\n", findMaxCalories(inputFile));
    fclose(inputFile);

    inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("error: file %s not found\n", filename);
        exit(1);
    }

    printf("Part 2: max calories = %d\n", findTopThreeMaxCalories(inputFile));
    fclose(inputFile);

    return 0;
}

int findMaxCalories(FILE *inputFile) {
    char line[BYTES_PER_LINE];
    int individualElfCalories = 0;
    int maxCalories = 0;

    while (fgets(line, BYTES_PER_LINE, inputFile)) {
        /* if not a new line, add calories to current elf's calorie count */
        if (atoi(line) != 0) {
            individualElfCalories += atoi(line);
        } else {
            if (individualElfCalories > maxCalories) {
                maxCalories = individualElfCalories;
            }

            individualElfCalories = 0;
        }
    }

    return maxCalories;
}

int findTopThreeMaxCalories(FILE *inputFile) {
    char line[BYTES_PER_LINE];
    int individualElfCalories = 0;
    int maxCalories[3];
    int elfNum = 0;

    while (fgets(line, BYTES_PER_LINE, inputFile)) {
        /* if not a new line, add calories to current elf's calorie count */
        if (atoi(line) != 0) {
            individualElfCalories += atoi(line);
        } else {
            if (elfNum < 3) {
                /* the first 3 elves' calorie counts are automatically the 3 largest to begin */
                maxCalories[elfNum] = individualElfCalories;
                elfNum++;
            } else {
                siftThroughTopThreeElfCalories(maxCalories, individualElfCalories);
            }
            
            individualElfCalories = 0;
        }
    }

    return maxCalories[0] + maxCalories[1] + maxCalories[2];
}

void siftThroughTopThreeElfCalories(int *maxCalories, int currentElfCalories) {
    /* sort the array to ensure the smallest of the 3 current max values is replaced */
    qsort(maxCalories, 3, sizeof(int), compare);

    for (int i = 0; i < 3; i++) {
        if (currentElfCalories > maxCalories[i]) {
            maxCalories[i] = currentElfCalories;
            break;
        }
    }
}

/* compare function for qsort() */
int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}
