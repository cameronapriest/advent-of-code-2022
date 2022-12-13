
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 250

#define RIGHT_ORDER 1
#define WRONG_ORDER 0

#define BLU "\x1B[34m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define PUR "\x1B[35m"
#define RED "\x1B[31m"
#define END "\x1B[0m"

int checkPairOrder(char *left, char *right);


int main(void) {
    FILE *inputFile = fopen("example.txt", "r");
    char line[LINE_SIZE];
    char left[LINE_SIZE];
    char right[LINE_SIZE];
    int lineNum = 0;
    int pairIndex = 1;
    int order;

    while (fgets(line, LINE_SIZE, inputFile)) {
        if (lineNum % 3 == 0) {
            strncpy(left, line, strlen(line) + 1);

        } else if (lineNum % 3 == 1) {
            strncpy(right, line, strlen(line) + 1);

        } else if (lineNum % 3 == 2) {
            printf("\nPair %d:\n", pairIndex);
            printf(BLU "  left:  " END "%s", left);
            printf(RED "  right: " END "%s", right);

            order = checkPairOrder(left, right);
            if (order == RIGHT_ORDER) {
                printf(GRN "right order\n" END);
            } else if (order == WRONG_ORDER) {
                printf(RED "wrong order\n" END);
            } else {
                printf(YEL "case not yet covered\n" END);
            }
            pairIndex++;
        }

        lineNum++;
    }

    printf("\n");

    return 0;
}

int checkPairOrder(char *left, char *right) {
    int i = 0;
    char *token;
    int l, r;

    while (left[i] != '\n' && right[i] != '\n') {
        printf("%c %c\n", left[i], right[i]);

        /* if both values are integers */
        if ((left[i] >= 48 && left[i] <= 57) &&
            (right[i] >= 48 && right[i] <= 57)) {
            
            l = atoi(&left[i]);
            r = atoi(&right[i]);

            if (l < r) {
                return RIGHT_ORDER;
            } else if (l > r) {
                return WRONG_ORDER;
            }

        /* if both values are lists */
        } else if (left[i] == '[' && right[i] == '[') {
            printf("list\n");

            //while (left[i] != ']' || right[i] != ']') {

            /* TODO - create recursive compareLists() function w/ params:
                char *left
                char *right
                int leftLength (including [ to ])
                int rightLength (including [ to ]) */

            i++;
            return checkPairOrder(&left[i], &right[i]);

        /* if exactly one value is an integer */
        } else if ((left[i] >= 48 && left[i] <= 57) && (right[i] < 48 || right[i] > 57)) {
            /* left is an integer, right is not */

            printf(PUR "left value is an integer\n" END);


        } else if ((right[i] >= 48 && right[i] <= 57) && (left[i] < 48 || left[i] > 57)) {
            /* right is an integer, left is not */

            printf(PUR "right value is an integer\n" END);
        }

        i++;
    }

    return -1;
}
