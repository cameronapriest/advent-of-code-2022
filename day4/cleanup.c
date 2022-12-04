
/* https://adventofcode.com/2022/day/4 */
/* gcc cleanup.c -o cleanup -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_LEN 20

void parseFile(FILE *inputFile);
int checkForFullyOverlappingPairs(int *nums);
int checkForOverlappingPairs(int *nums);


int main(void) {
    FILE *inputFile;
    char *filename = "input.txt";

    inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("error: file %s not found\n", filename);
        exit(1);
    }

    parseFile(inputFile);
    fclose(inputFile);

    return 0; 
}

void parseFile(FILE *inputFile) {
    char line[LINE_LEN];
    int fullyOverlappingPairs = 0;
    int overlappingPairs = 0;
    char *section;
    int sectionLimits[4];
    int sectionNum = 0;

    while (fgets(line, LINE_LEN, inputFile)) {
        section = strtok(line, "-");

        while (section) {
            sectionLimits[sectionNum] = atoi(section);
            sectionNum++;

            section = strtok(NULL, "-,");
        }

        if (checkForFullyOverlappingPairs(sectionLimits) == 1) {
            fullyOverlappingPairs++;
        }

        if (checkForOverlappingPairs(sectionLimits) == 1) {
            overlappingPairs++;
        }

        sectionNum = 0;
    }

    printf("Fully overlapping pairs: %d\n", fullyOverlappingPairs);
    printf("Total overlapping pairs: %d\n", overlappingPairs);
}

int checkForFullyOverlappingPairs(int *nums) {
    if (nums[0] >= nums[2] && nums[1] <= nums[3]) {
        return 1;
    } else if (nums[0] <= nums[2] && nums[1] >= nums[3]) {
        return 1;
    }

    return 0;
}

int checkForOverlappingPairs(int *nums) {
    if (nums[0] > nums[3]) {
        return 0;
    } else if (nums[1] < nums[2]) {
        return 0;
    }

    return 1;
}
