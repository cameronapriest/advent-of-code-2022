
/* https://adventofcode.com/2022/day/7 */
/* gcc space.c -o space -Wall -Wpedantic -Wextra */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BLU "\x1B[34m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define PUR "\x1B[35m"
#define RED "\x1B[31m"
#define END "\x1B[0m"

#define LINE_LEN 40

typedef struct file file;
typedef struct dir dir;

struct file {
    char *name;
    int size;
};

struct dir {
    char *dirName;
    file **files;
    int numFiles;
    dir **subdirectories;
    int numSubdirectories;
};

/* global */
dir *root;
dir *currentDir;

void parseCommand(char *line, char *parentDir);
dir *parseChangeDirectoryCommand(char *directory, dir *parentDir);
void parseOutput(char *line);

dir *createDirectory(char *dirName, dir *parentDir);

file *createFile(char *name, int size);

void addFileToDirectory(dir *d, file *f);

//void printFilesystem(dir *filesystem);

void printDirectory(dir *directory, int numSpaces);

int main(void) {
    FILE *inputFile = fopen("test-input.txt", "r");
    //FILE *inputFile = fopen("input.txt", "r");
    char line[LINE_LEN];

    /* dir *root = createDirectory("/", NULL);
    dir *currentDir = root;

    // dir **filesystem = (dir **) malloc(sizeof(dir));
    // filesystem[0] = root;
    

    dir *newDir = createDirectory("a", currentDir);
    createDirectory("p", newDir);
    createDirectory("b", currentDir);
    createDirectory("c", currentDir);

    printDirectory(root, 0);
    printf("--------------------------\n"); */

    //dir *filesystem = root;
    //printFilesystem(root);

    //dir *currentDir = NULL;


    dir *parentDir = (dir *) malloc(sizeof(dir));;

    while (fgets(line, LINE_LEN, inputFile)) {
        if (line[0] == '$') {
            printf("$ ");
            if (strncmp(&line[2], "cd", 2) == 0) {
                printf(BLU "cd " END);
                parentDir = parseChangeDirectoryCommand(&line[5], parentDir);
                
            } else if (strncmp(&line[2], "ls", 2) == 0) {
                printf(YEL "ls\n" END);
            }

        } else {
            parseOutput(line);
        }
    }

    printf("\n");
    printf("--------------------------\n");
    printDirectory(root, 0);
    printf("--------------------------\n");

    fclose(inputFile);

    return 0;
}

/* void parseCommand(char *line, char *parentDir) {
    printf("$ ");
    if (strncmp(line, "cd", 2) == 0) {
        printf(BLU "cd " END);
        parseChangeDirectoryCommand(&line[3], parentDir);
        
    } else if (strncmp(line, "ls", 2) == 0) {
        printf(YEL "ls\n" END);
    }
} */

dir *parseChangeDirectoryCommand(char *directory, dir *parentDir) {
    dir *dirToChangeTo = (dir *) malloc(sizeof(dir));

    if (strncmp(directory, "/", 1) == 0) {
        printf("/\n");
        root = createDirectory("/", NULL);
        dirToChangeTo = root;

    } else if (strncmp(directory, "..", 2) == 0) {
        printf("..\n");
        dirToChangeTo = parentDir;

    } else {
        printf("%s", directory);
        dirToChangeTo = createDirectory(directory, parentDir);
    }

    printf(GRN "dir to change to is %s" END, dirToChangeTo->dirName);
    printf("--------------------------\n");
    printDirectory(root, 0);
    printf("--------------------------\n");

    return dirToChangeTo;
}

void parseOutput(char *line) {
    printf("  %s", line);
}

/* void moveInOneLevel() {

} */

dir *createDirectory(char *dirName, dir *parentDir) {
    dir *newDir = (dir *) malloc(sizeof(dir));

    newDir->dirName = dirName;
    newDir->files = (file **) malloc(sizeof(file));;
    newDir->numFiles = 0;
    newDir->subdirectories = (dir **) malloc(sizeof(dir));;
    newDir->numSubdirectories = 0;

    if (parentDir) {
        printf(PUR "adding subdir %s to dir %s\n" END, newDir->dirName, parentDir->dirName);
        parentDir->subdirectories[parentDir->numSubdirectories] = newDir;
        parentDir->numSubdirectories++;
    }

    return newDir;
}

void printDirectory(dir *directory, int numSpaces) {
    for (int i = 0; i < numSpaces; i++) {
        printf(" ");
    }

    printf("- %s (dir) [%d]\n", directory->dirName, directory->numSubdirectories);

    if (directory->numSubdirectories != 0) {
        for (int i = 0; i < directory->numSubdirectories; i++) {
            printDirectory(directory->subdirectories[i], numSpaces + 2);
        }
    }
}
