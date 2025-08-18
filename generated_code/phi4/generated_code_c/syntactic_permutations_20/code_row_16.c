#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int OFFSET = 5;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long input_value = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid number: %s\n", argv[1]);
        return 1;
    }

    long result = input_value + OFFSET;
    printf("Result: %ld\n", result);
    return 0;
}