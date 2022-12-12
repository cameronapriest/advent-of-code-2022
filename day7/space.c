
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
    dir *parent;
    file **files;
    int numFiles;
    dir **subdirectories;
    int numSubdirectories;
    int totalSize;
};

/* globals - for code readability and ease of access from any function */
dir *root;
dir *currentDir = NULL;

void parseCommand(char *line);
void parseChangeDirectoryCommand(char *directory);
void parseOutput(char *line);

dir *createDirectory(char *dirName, dir *parent);
void printDirectory(dir *directory, int numSpaces);
void printSpaces(int numSpaces);

int calculateDirectorySizes(dir *d);
void findSmallestDir(dir *d, int bytesToBeDeleted, int *totalSizesSum);

void moveToRootDirectory(void);
void moveUpOneDirectory(void);
void moveDownOneDirectory(char *directory);

void createFile(char *line);


int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    char line[LINE_LEN];
    int totalSizesSum = 0;
    int bytesToBeDeleted = 0;

    root = createDirectory("/", NULL);
    currentDir = root; 

    while (fgets(line, LINE_LEN, inputFile)) {
        line[strcspn(line, "\n")] = '\0'; /* remove trailing '\n' */

        if (line[0] == '$') {
            parseCommand(line);
        } else {
            parseOutput(line);
        }
    }

    calculateDirectorySizes(root);
    bytesToBeDeleted = 30000000 - (70000000 - root->totalSize);

    printf("----------------------------------------------------\n");
    printDirectory(root, 0);
    printf("----------------------------------------------------\n");

    findSmallestDir(root, bytesToBeDeleted, &totalSizesSum);
    printf("\nsum of directories with size < 100000 = %d\n\n", totalSizesSum);

    /* TODO - free everything recursively */

    fclose(inputFile);

    return 0;
}

void parseCommand(char *line) {
    if (strncmp(&line[2], "cd", 2) == 0) {
        parseChangeDirectoryCommand(&line[5]);
    }
}

void parseChangeDirectoryCommand(char *directory) {
    if (strncmp(directory, "/", 1) == 0) {
        moveToRootDirectory();
    } else if (strncmp(directory, "..", 2) == 0) {
        moveUpOneDirectory();
    } else {
        moveDownOneDirectory(directory);
    }
}

void moveToRootDirectory() {
    currentDir = root;
}

void moveUpOneDirectory() {
    currentDir = currentDir->parent;
}

void moveDownOneDirectory(char *directory) {
    for (int i = 0; i < currentDir->numSubdirectories; i++) {
        if (strcmp(currentDir->subdirectories[i]->dirName, directory) == 0) {
            currentDir = currentDir->subdirectories[i];
            break;
        }
    }
}

void parseOutput(char *line) {
    if (strncmp(line, "dir", 3) == 0) {
        createDirectory(&line[4], currentDir);
    } else {
        createFile(line);
    }
}

void createFile(char *line) {
    file *newFile = (file *) malloc(sizeof(file));
    char *token;

    token = strtok(line, " ");
    if (token) {
        newFile->size = atoi(token);
    }

    token = strtok(NULL, "\n");
    if (token) {
        newFile->name = (char *) malloc(sizeof(char));
        strncpy(newFile->name, token, strlen(token) + 1);
    }

    currentDir->files = (file **) realloc(currentDir->files, 
        sizeof(file) * (currentDir->numFiles + 1));
    currentDir->files[currentDir->numFiles] = newFile;
    currentDir->numFiles++;
}

dir *createDirectory(char *dirName, dir *parent) {
    dir *newDir = (dir *) malloc(sizeof(dir));
    
    newDir->dirName = (char *) malloc(sizeof(char) * strlen(dirName));
    strncpy(newDir->dirName, dirName, strlen(dirName) + 1);

    newDir->parent = parent;
    newDir->files = (file **) malloc(sizeof(file));
    newDir->numFiles = 0;
    newDir->subdirectories = (dir **) malloc(sizeof(dir));
    newDir->numSubdirectories = 0;
    newDir->totalSize = 0;

    if (parent) {
        parent->subdirectories = (dir **) realloc(parent->subdirectories, 
            sizeof(dir) * (parent->numSubdirectories + 1));
        parent->subdirectories[parent->numSubdirectories] = newDir;
        parent->numSubdirectories++;
    }

    return newDir;
}

int calculateDirectorySizes(dir *d) {
    if (d->numFiles != 0) {
        for (int i = 0; i < d->numFiles; i++) {
            d->totalSize += d->files[i]->size;
        }
    }

    if (d->numSubdirectories != 0) {
        for (int i = 0; i < d->numSubdirectories; i++) {
            d->totalSize += calculateDirectorySizes(d->subdirectories[i]);
        }
    }

    return d->totalSize;
}

void printDirectory(dir *d, int numSpaces) {
    printSpaces(numSpaces);
    printf("- %s (dir) [%d]\n", d->dirName, d->totalSize);

    if (d->numFiles != 0) {
        for (int i = 0; i < d->numFiles; i++) {
            printSpaces(numSpaces + 2);
            printf("- %s (file, size=%d)\n", d->files[i]->name, d->files[i]->size);
        }
    }

    if (d->numSubdirectories != 0) {
        for (int i = 0; i < d->numSubdirectories; i++) {
            printDirectory(d->subdirectories[i], numSpaces + 2);
        }
    }
}

void findSmallestDir(dir *d, int bytesToBeDeleted, int *totalSizesSum) {
    if (d->totalSize <= 100000) { /*  part 1 */
        *totalSizesSum += d->totalSize;
    }

    if (d->totalSize >= bytesToBeDeleted) { /* part 2 */
        printf("dir %s, size %d >= %d\n", d->dirName, d->totalSize, bytesToBeDeleted);
    }

    if (d->numSubdirectories != 0) {
        for (int i = 0; i < d->numSubdirectories; i++) {
            findSmallestDir(d->subdirectories[i], bytesToBeDeleted, totalSizesSum);
        }
    }
}

void printSpaces(int numSpaces) {
    for (int i = 0; i < numSpaces; i++) {
        printf(" ");
    }
}
