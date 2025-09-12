#include <stdio.h>
#include <stdlib.h>

int convertStringToInt(const char *str) {
    return atoi(str);
}

void printArgument(int index, int argc, char *argv[]) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        printf("Index out of bounds.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <command-line argument index>\n", argv[0]);
        return 1;
    }

    int argIndex = convertStringToInt(argv[1]);
    int commandArgIndex = convertStringToInt(argv[2]);

    printArgument(commandArgIndex, argc, argv);

    return 0;
}