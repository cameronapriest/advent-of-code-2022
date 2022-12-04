
/* https://adventofcode.com/2022/day/3 */
/* gcc rucksack.c -o rucksack -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_RUCKSACK_SIZE 60

/*  see https://www.asciitable.com/ and note:
 *      Lowercase item types a through z have priorities 1 through 26.
 *      Uppercase item types A through Z have priorities 27 through 52.
 */
#define LOWERCASE_PRIORITY_OFFSET 96
#define UPPERCASE_PRIORITY_OFFSET 38

void parseFilePartOne(FILE *inputFile);
int mapPriority(char itemType);

void parseFilePartTwo(FILE *inputFile);
int findPriorityOfMatchingTriplet(char rucksackGroup[3][MAX_RUCKSACK_SIZE]);


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
    char *itemType;

    while (fgets(rucksack, MAX_RUCKSACK_SIZE, inputFile)) {
        compartmentSize = (strlen(rucksack) - 1) / 2;

        /* check for the only item type that appears in 
           both compartments of the rucksack */
        for (int i = 0; i < compartmentSize; i++) {
            for (int j = compartmentSize; j < compartmentSize * 2; j++) {
                if (rucksack[i] == rucksack[j]) {
                    sumOfPriorities += mapPriority(rucksack[i]);
                    goto breakPoint;
                }
            }
        }

        /* less readable, I think; I'll leave it commented out as an alternative */
        /* for (int i = 0; i < compartmentSize; i++) {
            if ((itemType = strchr(&rucksack[compartmentSize], rucksack[i])) != NULL) {
                sumOfPriorities += mapPriority(rucksack[i]);
                goto breakPoint;
            }
        } */
        
        breakPoint: continue;
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
    char rucksackGroup[3][MAX_RUCKSACK_SIZE];
    int sumOfPriorities = 0;
    int lineNum = 0;

    while (fgets(rucksackGroup[lineNum], MAX_RUCKSACK_SIZE, inputFile)) {
        lineNum++;

        if (lineNum == 3) {
            sumOfPriorities += findPriorityOfMatchingTriplet(rucksackGroup);
            lineNum = 0;
        }
    }

    printf("priority sums: %d\n", sumOfPriorities);
}

int findPriorityOfMatchingTriplet(char rucksackGroup[3][MAX_RUCKSACK_SIZE]) {
    char *itemTypeGroupTwo;
    char *itemTypeGroupThree;
    int potentialBadge;
    
    /* find matching triplet of item type across all three rucksacks in the group */
    for (int i = 0; i < (int) strlen(rucksackGroup[0]) - 1; i++) {
        potentialBadge = (int) rucksackGroup[0][i];

        if ((itemTypeGroupTwo = strchr(rucksackGroup[1], potentialBadge)) != NULL) {
            if ((itemTypeGroupThree = strchr(rucksackGroup[2], potentialBadge)) != NULL) {
                return mapPriority(itemTypeGroupTwo[0]);
            }
        }
    }

    printf("input error\n");
    exit(1);
}
