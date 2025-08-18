#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int input = atoi(argv[1]);
    const int offset = 1000;
    int result = input + offset;

    printf("Input value: %d\n", input);
    printf("Value after adding offset of 1000: %d\n", result);

    return EXIT_SUCCESS;
}