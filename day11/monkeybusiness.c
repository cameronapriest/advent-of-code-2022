
/* https://adventofcode.com/2022/day/11 */
/* gcc monkeybusiness.c -o monkeybusiness -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 50

typedef struct {
    int num;
    int items[100];
    int numItems;
    char operation;
    char operand[3];
    int divisibleBy;
    int trueConditionNextMonkey;
    int falseConditionNextMonkey;
    int itemsInspected;
} monkey;

void parseMonkey(char *line, monkey *m);
void printMonkey(monkey *m);
void simulateRound(monkey **monkeys, int numMonkeys, int round);
void inspectItem(monkey **monkeys, monkey *m, int itemIndex);
void throwItemToMonkey(monkey **monkeys, int item, int receivingMonkey);


int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    char line[LINE_SIZE];
    monkey *monkeys[10];
    int numMonkeys = 0;

    for (int i = 0; i < 10; i++) {
        monkeys[i] = (monkey *) malloc(sizeof(monkey));
    }

    while (fgets(line, LINE_SIZE, inputFile)) {
        if (line[0] == '\n') {
            numMonkeys++;
        }

        parseMonkey(line, monkeys[numMonkeys]);
    }

    for (int round = 1; round <= 10000; round++) {
        simulateRound(monkeys, numMonkeys, round);
    }

    for (int i = 0; i < 10; i++) {
        free(monkeys[i]);
    }

    printf("\n");
    fclose(inputFile);

    return 0;
}

void simulateRound(monkey **monkeys, int numMonkeys, int round) {
    for (int i = 0; i <= numMonkeys; i++) {
        for (int j = 0; j < monkeys[i]->numItems; j++) {
            inspectItem(monkeys, monkeys[i], j);
        }

        monkeys[i]->numItems = 0;
    }

    if (/* round % 1000 == 0 ||  */round == 1 || round == 20) {
        printf("\n---- ROUND %d COMPLETE ----\n", round);

        for (int i = 0; i <= numMonkeys; i++) {
            printMonkey(monkeys[i]);
        }
    }
}

void inspectItem(monkey **monkeys, monkey *m, int itemIndex) {
    if (m->operation == '*') {
        if (strncmp(m->operand, "old", 3) == 0) {
            m->items[itemIndex] = m->items[itemIndex] * m->items[itemIndex];
        } else {
            m->items[itemIndex] = m->items[itemIndex] * atoi(m->operand);
        }
    } else if (m->operation == '+') {
        if (strncmp(m->operand, "old", 3) == 0) {
            m->items[itemIndex] = m->items[itemIndex] + m->items[itemIndex];
        } else {
            m->items[itemIndex] = m->items[itemIndex] + atoi(m->operand);
        }
    }

    /* part 2 - Worry levels are no longer divided by three after each item is inspected */
    m->items[itemIndex] = m->items[itemIndex] / 3;

    if (m->items[itemIndex] % m->divisibleBy == 0) {
        throwItemToMonkey(monkeys, m->items[itemIndex], m->trueConditionNextMonkey);
    } else {
        throwItemToMonkey(monkeys, m->items[itemIndex], m->falseConditionNextMonkey);
    }

    m->itemsInspected++;
}

void throwItemToMonkey(monkey **monkeys, int item, int receivingMonkey) {
    monkeys[receivingMonkey]->items[monkeys[receivingMonkey]->numItems] = item;
    monkeys[receivingMonkey]->numItems++;
}

void parseMonkey(char *line, monkey *m) {
    char *token = NULL;

    if (strncmp(line, "Monkey", 6) == 0) {
        m->num = atoi(&line[7]);

    } else if (strncmp(line, "  Starting", 10) == 0) {
        m->numItems = 0;
        token = strtok(&line[18], ", ");

        while (token) {
            m->items[m->numItems] = atoi(token);
            m->numItems++;
            token = strtok(NULL, ", ");
        }

    } else if (strncmp(line, "  Operation", 11) == 0) {
        m->operation = line[23];
        memcpy(m->operand, &line[25], sizeof(char) * 3);

    } else if (strncmp(line, "  Test", 6) == 0) {
        m->divisibleBy = atoi(&line[21]);

    } else if (strncmp(line, "    If true:", 12) == 0) {
        m->trueConditionNextMonkey = atoi(&line[29]);

    } else if (strncmp(line, "    If false:", 13) == 0) {
        m->falseConditionNextMonkey = atoi(&line[30]);

        m->itemsInspected = 0;
     
        printMonkey(m);
    }
}

void printMonkey(monkey *m) {
    printf("\n----------------------------------------\n");

    printf("Monkey [%d]\n", m->num);

    printf("  Starting items: {");
    for (int i = 0; i < m->numItems; i++) {
        printf("%d, ", m->items[i]);
    }
    printf("}\n");

    printf("  Operation: new = old %c ", m->operation);
    if (strncmp(m->operand, "old", 3) == 0) {
        printf("old\n");
    } else {
        printf("%d\n", atoi(m->operand));
    }

    printf("  Test: divisible by %d\n", m->divisibleBy);
    printf("    if true: throw to monkey %d\n", m->trueConditionNextMonkey);
    printf("    if false: throw to monkey %d\n", m->falseConditionNextMonkey);
    printf("  Items inspected: %d\n", m->itemsInspected);
}
