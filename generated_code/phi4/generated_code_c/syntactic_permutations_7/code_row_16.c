#include <stdio.h>
#include <stdlib.h>

int convertStringToInt(const char *str) {
    return atoi(str);
}

void printArgument(int index) {
    printf("%s\n", argv[index]);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <other arguments>\n", argv[0]);
        return 1;
    }

    int index = convertStringToInt(argv[1]);

    if (index < 1 || index >= argc) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    printArgument(index);

    return 0;
}