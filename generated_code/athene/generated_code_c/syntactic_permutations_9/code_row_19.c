#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <index> [arguments...]\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]) + 1;

    if (index >= argc || index <= 1) {
        printf("Index out of range.\n");
        return 1;
    }

    printf("The %d argument from the command line is: %s\n", index - 1, argv[index]);
    return 0;
}