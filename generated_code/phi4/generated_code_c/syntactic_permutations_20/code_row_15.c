#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int value = atoi(argv[1]);
    const int offset = 10; // Change this constant to your desired offset

    int result = value + offset;

    printf("Result: %d\n", result);

    return EXIT_SUCCESS;
}