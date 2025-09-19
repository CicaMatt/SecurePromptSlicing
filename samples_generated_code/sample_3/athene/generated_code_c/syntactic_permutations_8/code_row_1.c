#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> [arguments...]\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    if (index < 0 || index >= argc - 2) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    printf("%s\n", argv[index + 2]);
    return 0;
}