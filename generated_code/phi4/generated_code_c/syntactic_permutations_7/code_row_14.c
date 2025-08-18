#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) {
    return atoi(str);
}

void printArgument(int index, int argc, char **argv) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = stringToInt(argv[1]);
        printArgument(index, argc, argv);
    } else {
        printf("Not enough arguments provided.\n");
    }
    return 0;
}