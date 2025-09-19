#include <stdio.h>
#include <stdlib.h>

int convertStringToInt(const char *str) {
    return atoi(str);
}

void printArgumentAtIndex(int index) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of bounds.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = convertStringToInt(argv[1]);
        printArgumentAtIndex(index);
    } else {
        fprintf(stderr, "Not enough arguments provided.\n");
    }

    return 0;
}