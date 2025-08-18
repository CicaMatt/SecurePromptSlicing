#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index >= argc) {
        printf("Index out of bounds\n");
        return 1;
    }

    printf("Value at index %d is %s\n", index, argv[index]);

    return 0;
}