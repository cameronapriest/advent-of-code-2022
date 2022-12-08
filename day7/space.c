
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
};

/* global */
dir *root;
dir *currentDir = NULL;

void parseCommand(char *line);
void parseChangeDirectoryCommand(char *directory);
void parseOutput(char *line);

dir *createDirectory(char *dirName, dir *parent);
void printDirectory(dir *directory, int numSpaces);
void printSpaces(int numSpaces);

void moveToRootDirectory(void);
void moveUpOneDirectory(void);
void moveDownOneDirectory(char *directory);

file *createFile(char *line);


int main(void) {
    FILE *inputFile = fopen("test-input.txt", "r");
    //FILE *inputFile = fopen("input.txt", "r");
    char line[LINE_LEN];

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

    printf("\n");
    printf("--------------------------\n");
    printDirectory(root, 0);
    printf("--------------------------\n");

    fclose(inputFile);

    return 0;
}

void parseCommand(char *line) {
    printf("$ ");
    if (strncmp(&line[2], "cd", 2) == 0) {
        printf(BLU "cd " END);
        parseChangeDirectoryCommand(&line[5]);
        
    } else if (strncmp(&line[2], "ls", 2) == 0) {
        printf(BLU "ls\n" END);
    }
}

void parseChangeDirectoryCommand(char *directory) {
    if (strncmp(directory, "/", 1) == 0) {
        printf("/\n");
        moveToRootDirectory();

    } else if (strncmp(directory, "..", 2) == 0) {
        printf("..\n");
        moveUpOneDirectory();

    } else {
        printf("%s\n", directory);
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
    int found = 0;

    for (int i = 0; i < currentDir->numSubdirectories; i++) {
        /* printf("\t|%s|\n", currentDir->subdirectories[i]->dirName); */

        if (strcmp(currentDir->subdirectories[i]->dirName, directory) == 0) {
            currentDir = currentDir->subdirectories[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        printf(RED "ERROR: subdirectory %s not found in parent directory %s\n" END, 
            directory, currentDir->dirName);
        exit(1);
    }
}

void parseOutput(char *line) {
    if (strncmp(line, "dir", 3) == 0) {
        createDirectory(&line[4], currentDir);
        printf(GRN "  dir %s\n" END, &line[4]);
    } else {
        file *f = createFile(line);
        printf(YEL "  %s " END "%d\n", f->name, f->size);
    }
}

file *createFile(char *line) {
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

    /* printf(PUR "\tadding file [%s] to dir [%s] at %d\n" END, newFile->name, 
        currentDir->dirName, currentDir->numFiles); */

    currentDir->files = (file **) realloc(currentDir->files, sizeof(file) * (currentDir->numFiles + 1));
    currentDir->files[currentDir->numFiles] = newFile;
    currentDir->numFiles++;

    /* printf("--------------------------\n");
    printDirectory(currentDir, 0);
    printf("--------------------------\n"); */

    return newFile;
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

    /* printf(BLU "new dir %s created\n" END, newDir->dirName); */

    if (parent) {
        /* printf(PUR "\tadding subdir [%s] to dir [%s] at %d\n" END, 
            newDir->dirName, parent->dirName, parent->numSubdirectories); */

        parent->subdirectories = (dir **) realloc(parent->subdirectories, 
            sizeof(dir) * (parent->numSubdirectories + 1));
        parent->subdirectories[parent->numSubdirectories] = newDir;
        parent->numSubdirectories++;

        /* printf("--------------------------\n");
        printDirectory(parent, 0);
        printf("--------------------------\n"); */
    }

    return newDir;
}

void printDirectory(dir *d, int numSpaces) {
    printSpaces(numSpaces);

    printf("- %s (dir) [%d]\n", d->dirName, d->numSubdirectories);

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

void printSpaces(int numSpaces) {
    for (int i = 0; i < numSpaces; i++) {
        printf(" ");
    }
}
