
/* https://adventofcode.com/2022/day/3 */
/* gcc rucksack-alt.c -o rucksack-alt -Wall -Wpedantic -Wextra */
/* alternate solution with bitwise logic */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_RUCKSACK_SIZE 60

/*  see https://www.asciitable.com/ and note:
 *      Lowercase item types a through z have priorities 1 through 26.
 *      Uppercase item types A through Z have priorities 27 through 52.
 */
#define LOWERCASE_PRIORITY_OFFSET 96
#define UPPERCASE_PRIORITY_OFFSET 38

void parseFilePartOne(FILE *inputFile);
void parseFilePartTwo(FILE *inputFile);
int mapPriority(char itemType);


int main(void) {
    FILE *inputFile;
    char *filename = "input.txt";

    inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("error: file %s not found\n", filename);
        exit(1);
    }

    parseFilePartOne(inputFile);
    fclose(inputFile);

    inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("error: file %s not found\n", filename);
        exit(1);
    }

    parseFilePartTwo(inputFile);
    fclose(inputFile);

    return 0;
}

void parseFilePartOne(FILE *inputFile) {
    char rucksack[MAX_RUCKSACK_SIZE];
    int compartmentSize;
    int sumOfPriorities = 0;
    uint64_t compartments[2];
    char commonItemType;

    while (fgets(rucksack, MAX_RUCKSACK_SIZE, inputFile)) {
        compartmentSize = (strlen(rucksack) - 1) / 2;
        compartments[0] = 0LL;
        compartments[1] = 0LL;

        for (int i = 0; i < compartmentSize; i++) {
            compartments[0] |= (uint64_t) (1LL << (rucksack[i] - 65));
            compartments[1] |= (uint64_t) (1LL << (rucksack[i + compartmentSize] - 65));
        }
        
        commonItemType = (char) log2l(compartments[0] & compartments[1]);
        sumOfPriorities += mapPriority(commonItemType + 65);
    }

    printf("priority sums: %d\n", sumOfPriorities);
}

int mapPriority(char itemType) {
    if (itemType >= 'a' && itemType <= 'z') {
        return (itemType - LOWERCASE_PRIORITY_OFFSET);

    } else if (itemType >= 'A' && itemType <= 'Z') {
        return (itemType - UPPERCASE_PRIORITY_OFFSET);
    }
        
    printf("parsing/input error\n");
    exit(1);
}

void parseFilePartTwo(FILE *inputFile) {
    char rucksack[MAX_RUCKSACK_SIZE];
    int rucksackSize;
    int sumOfPriorities = 0;
    uint64_t rucksackGroup[3] = {0LL, 0LL, 0LL};
    char commonItemType;
    int lineNum = 0;

    while (fgets(rucksack, MAX_RUCKSACK_SIZE, inputFile)) {
        rucksackSize = strlen(rucksack) - 1;

        for (int i = 0; i < rucksackSize; i++) {
            rucksackGroup[lineNum] |= (uint64_t) (1LL << (rucksack[i] - 65));
        }

        lineNum++;

        if (lineNum == 3) {
            commonItemType = (char) log2l(rucksackGroup[0] & rucksackGroup[1] & rucksackGroup[2]);
            sumOfPriorities += mapPriority(commonItemType + 65);

            /* reset group values + line num to zero */
            memset(rucksackGroup, 0, sizeof(uint64_t) * 3);
            lineNum = 0;
        }
    }

    printf("priority sums: %d\n", sumOfPriorities);
}
