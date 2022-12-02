
/* https://adventofcode.com/2022/day/2 */
/* gcc rockpaperscissors.c -o rpc -Wall -Wpedantic -Wextra */
/* verbose solution, but gets the job done */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BYTES_PER_LINE 5

#define OPPONENT_ROCK 'A'
#define OPPONENT_PAPER 'B'
#define OPPONENT_SCISSORS 'C'

/* part 1 X, Y, Z */
#define SELF_ROCK 'X'
#define SELF_PAPER 'Y'
#define SELF_SCISSORS 'Z'

/* part 2 X, Y, Z */
#define NEED_TO_LOSE 'X'
#define NEED_TO_DRAW 'Y'
#define NEED_TO_WIN 'Z'

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define LOSE 0
#define DRAW 3
#define WIN 6

#define OPPONENT_INDEX 0
#define SELF_INDEX 2

void parseFilePartOne(FILE *inputFile);
int determineRoundOutcome(char opponent, char self);

void parseFilePartTwo(FILE *inputFile);
int fixRoundOutcome(char opponent, char roundOutcome);

/*  opponent        self                      
 *  rock = A        rock = X        (1 point)
 *  paper = B       paper = Y       (2 points)
 *  scissors = C    scissors = Z    (3 points)
 *
 *  lose = 0 points
 *  draw = 3 points
 *  win = 6 points
 */

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
    char line[BYTES_PER_LINE];
    int score = 0;

    while (fgets(line, BYTES_PER_LINE, inputFile)) {
        switch (line[SELF_INDEX]) {
            case SELF_ROCK:
                score += ROCK;
                break;
            case SELF_PAPER:
                score += PAPER;
                break;
            case SELF_SCISSORS:
                score += SCISSORS;
                break;
        }

        score += determineRoundOutcome(line[OPPONENT_INDEX], line[SELF_INDEX]);
    }

    printf("Part 1: score: %d\n", score);
}

int determineRoundOutcome(char opponent, char self) {
    if ((opponent == OPPONENT_ROCK && self == SELF_ROCK) || 
        (opponent == OPPONENT_PAPER && self == SELF_PAPER) ||
        (opponent == OPPONENT_SCISSORS && self == SELF_SCISSORS)) {

        return DRAW;

    } else if ((opponent == OPPONENT_ROCK && self == SELF_SCISSORS) ||
        (opponent == OPPONENT_SCISSORS && self == SELF_PAPER) ||
        (opponent == OPPONENT_PAPER && self == SELF_ROCK)) {

        return LOSE;

    } else if ((opponent == OPPONENT_SCISSORS && self == SELF_ROCK) ||
        (opponent == OPPONENT_PAPER && self == SELF_SCISSORS) ||
        (opponent == OPPONENT_ROCK && self == SELF_PAPER)) {
        
        return WIN;

    } else {
        printf("logic error\n");
        exit(1);
    }
}

void parseFilePartTwo(FILE *inputFile) {
    char line[BYTES_PER_LINE];
    int score = 0;

    while (fgets(line, BYTES_PER_LINE, inputFile)) {
        score += fixRoundOutcome(line[OPPONENT_INDEX], line[SELF_INDEX]);
    }

    printf("Part 2: score: %d\n", score);
}

int fixRoundOutcome(char opponent, char roundOutcome) {
    if (opponent == OPPONENT_ROCK) {
        if (roundOutcome == NEED_TO_DRAW) {
            return ROCK + DRAW;
        } else if (roundOutcome == NEED_TO_WIN) {
            return PAPER + WIN;
        } else if (roundOutcome == NEED_TO_LOSE) {
            return SCISSORS + LOSE;
        }

    } else if (opponent == OPPONENT_PAPER) {
        if (roundOutcome == NEED_TO_DRAW) {
            return PAPER + DRAW;
        } else if (roundOutcome == NEED_TO_WIN) {
            return SCISSORS + WIN;
        } else if (roundOutcome == NEED_TO_LOSE) {
            return ROCK + LOSE;
        }

    } else if (opponent == OPPONENT_SCISSORS) {
        if (roundOutcome == NEED_TO_DRAW) {
            return SCISSORS + DRAW;
        } else if (roundOutcome == NEED_TO_WIN) {
            return ROCK + WIN;
        } else if (roundOutcome == NEED_TO_LOSE) {
            return PAPER + LOSE;
        }
    }

    printf("logic error\n");
    exit(1);
}
