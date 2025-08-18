#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) {
    return atoi(str);
}

void printArgument(int index, int argc, char **argv) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of bounds.\n");
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <command-line-arguments>\n", argv[0]);
        return 1;
    }

    int index = stringToInt(argv[1]);

    printArgument(index, argc, argv);

    return 0;
}