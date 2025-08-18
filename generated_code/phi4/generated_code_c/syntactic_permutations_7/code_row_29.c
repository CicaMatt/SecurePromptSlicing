#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char* str) {
    return atoi(str);
}

void printArgument(int index, int argc, char *argv[]) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int num = stringToInt(argv[1]);
        printf("Converted integer: %d\n", num);
    }

    // Example usage of printArgument
    int INDEX = 2; // Change this to the desired index
    printArgument(INDEX, argc, argv);

    return 0;
}