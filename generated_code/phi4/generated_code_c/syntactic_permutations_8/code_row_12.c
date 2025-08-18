#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <arg1> <arg2> ... <argN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = atoi(argv[1]);

    // Check for valid index
    if (index < 1 || index >= argc) {
        fprintf(stderr, "Error: Index out of range\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", argv[index]);
    return EXIT_SUCCESS;
}