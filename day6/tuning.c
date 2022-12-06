
/* https://adventofcode.com/2022/day/6 */
/* gcc tuning.c -o tuning -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_LEN 4096

int findSequenceOfDifferentCharacters(char *marker, int numCharacters);

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    char line[LINE_LEN];
    int i = 0;

    while (fgets(line, LINE_LEN, inputFile)) {
        while (i < LINE_LEN - 4) {
            if (findSequenceOfDifferentCharacters(&line[i], 4) == 1) {
                printf("%d\n", i + 4);
                break;
            }

            i++;
        }

        while (i < LINE_LEN - 4) {
            if (findSequenceOfDifferentCharacters(&line[i], 14) == 1) {
                printf("%d\n", i + 14);
                break;
            }

            i++;
        }
    }

    fclose(inputFile);
    
    return 0;
}

int findSequenceOfDifferentCharacters(char *marker, int numCharacters) {
    for (int i = 0; i < numCharacters; i++) {
        for (int j = 0; j < numCharacters; j++) {
            if (i != j) {
                if (marker[i] == marker[j]) {
                    return 0;
                }
            }
        }
    }

    return 1;
}
