#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) {
    return atoi(str);
}

void printArgAtIndex(int index) {
    if (index < 1 || index >= argc) {
        printf("Index out of range\n");
        return;
    }
    printf("%s\n", argv[index]);
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Not enough arguments provided.\n");
        return 1;
    }

    int index = stringToInt(argv[1]);
    printArgAtIndex(index);

    return 0;
}