#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long input = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid number\n");
        return 1;
    }

    long result = input + 1000;

    printf("Result: %ld\n", result);
    return 0;
}