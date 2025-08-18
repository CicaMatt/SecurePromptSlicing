#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) {
    return atoi(str);
}

void printArgument(int argc, char *argv[], int index) {
    if (index >= 0 && index < argc - 1) {
        printf("%s\n", argv[index + 1]);
    } else {
        fprintf(stderr, "Index out of bounds.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = stringToInt(argv[1]);
    printArgument(argc, argv, index);

    return 0;
}