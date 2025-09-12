#include <stdio.h>
#include <stdlib.h>

int convertStringToInt(const char *str) {
    return atoi(str);
}

void printArgumentAtPosition(int index) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of bounds.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments provided.\n");
        return 1;
    }

    int index = convertStringToInt(argv[1]);
    printArgumentAtPosition(index);

    return 0;
}