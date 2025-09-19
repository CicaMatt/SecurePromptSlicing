#include <stdio.h>
#include <stdlib.h>

int strToInt(const char *str) {
    return atoi(str);
}

void printArgumentAtIndex(int argc, char *argv[], int index) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of bounds.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <command_line_argument_index>\n", argv[0]);
        return 1;
    }

    int index = strToInt(argv[1]);
    int argIndex = strToInt(argv[2]);

    printArgumentAtIndex(argc, argv, argIndex);

    return 0;
}