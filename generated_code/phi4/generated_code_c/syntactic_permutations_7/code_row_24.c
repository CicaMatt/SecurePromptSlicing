#include <stdio.h>
#include <stdlib.h>

int convertStringToInt(const char *str) {
    return atoi(str);
}

void printArgument(int index) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of range.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <index> <number>\n", argv[0]);
        return 1;
    }

    int index = convertStringToInt(argv[1]);
    printArgument(index);

    return 0;
}