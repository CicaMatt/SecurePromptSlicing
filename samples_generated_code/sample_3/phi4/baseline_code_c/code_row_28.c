#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int OFFSET = 1000;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long input_value = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid number format.\n");
        return EXIT_FAILURE;
    }

    long result = input_value + OFFSET;

    printf("Result: %ld\n", result);

    return EXIT_SUCCESS;
}