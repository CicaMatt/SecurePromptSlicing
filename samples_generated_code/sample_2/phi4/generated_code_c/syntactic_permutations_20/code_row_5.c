#include <stdio.h>
#include <stdlib.h>

#define OFFSET 5

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int value = atoi(argv[1]);
    int result = value + OFFSET;

    printf("Result: %d\n", result);
    return EXIT_SUCCESS;
}