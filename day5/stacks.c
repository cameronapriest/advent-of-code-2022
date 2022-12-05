
/* https://adventofcode.com/2022/day/5 */
/* gcc stacks.c -o stacks -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* manually parsed the initial stacks:

    [B]             [B] [S]        
    [M]             [P] [L] [B] [J]
    [D]     [R]     [V] [D] [Q] [D]
    [T] [R] [Z]     [H] [H] [G] [C]
    [P] [W] [J] [B] [J] [F] [J] [S]
[N] [S] [Z] [V] [M] [N] [Z] [F] [M]
[W] [Z] [H] [D] [H] [G] [Q] [S] [W]
[B] [L] [Q] [W] [S] [L] [J] [W] [Z]
 1   2   3   4   5   6   7   8   9  */

typedef struct {
    char crates[56];    /* crates, from bottom to top */
    int stackSize;      /* number of crates in stack */
    int stackNum;       /* stack number (1-9) */
} stack;

void createStack(stack *s, char *crates, int stackSize, int stackNum);
void removeCratesFromStack(stack *s, int numCratesToRemove, char *removedCrates);
void addCratesToStack(stack *s, int numCratesToAdd, char *cratesToAdd);
void addCratesToStackInOrder(stack *s, int numCratesToAdd, char *cratesToAdd);
void printStackBottomToTop(stack *s);

int main(void) {
    FILE *f = fopen("input.txt", "r");

    stack stacks[9];
    int initialStackSizes[9] = {3, 8, 5, 6, 4, 8, 8, 7, 7};
    char *initialStackValues[9] = {"BWN", "LZSPTDMB", "QHZWR", "WDVJZR", "SHMB", 
        "LGNJHVPB", "JQZFHDLS", "WSFJGQB", "ZWMSCDJ"};

    int numCratesToMove, currentStackNum, toStackNum;
    char removedCrates[56];

    for (int i = 0; i < 9; i++) {
        createStack(&stacks[i], initialStackValues[i], initialStackSizes[i], i + 1);
        printStackBottomToTop(&stacks[i]);
    }

    while (fscanf(f, "move %d from %d to %d ", &numCratesToMove, &currentStackNum, &toStackNum) != EOF) {
        removeCratesFromStack(&stacks[currentStackNum - 1], numCratesToMove, removedCrates);
        addCratesToStackInOrder(&stacks[toStackNum - 1], numCratesToMove, removedCrates);
        /* addCratesToStack(&stacks[toStackNum - 1], numCratesToMove, removedCrates); */
    }

    fclose(f);

    printf("\n");
    for (int i = 0; i < 9; i++) {
        printStackBottomToTop(&stacks[i]);
    }

    return 0;
}

void createStack(stack *s, char *crates, int stackSize, int stackNum) {
    memcpy(s->crates, crates, stackSize);
    s->stackSize = stackSize;
    s->stackNum = stackNum;
}

void removeCratesFromStack(stack *s, int numCratesToRemove, char *removedCrates) {
    for (int i = 0; i < numCratesToRemove; i++) {
        removedCrates[i] = s->crates[s->stackSize - 1];
        s->stackSize--;
    }
}

/* part 1 */
void addCratesToStack(stack *s, int numCratesToAdd, char *cratesToAdd) {
    for (int i = 0; i < numCratesToAdd; i++) {
        s->crates[s->stackSize] = cratesToAdd[i];
        s->stackSize++;
    }
}

/* part 2 */
void addCratesToStackInOrder(stack *s, int numCratesToAdd, char *cratesToAdd) {
    for (int i = numCratesToAdd - 1; i >= 0; i--) {
        s->crates[s->stackSize] = cratesToAdd[i];
        s->stackSize++;
    }
}

void printStackBottomToTop(stack *s) {
    printf("stack %d: ", s->stackNum);

    for (int i = 0; i < s->stackSize; i++) {
        printf("[%c] ", s->crates[i]);
    }

    printf("\n");
}
