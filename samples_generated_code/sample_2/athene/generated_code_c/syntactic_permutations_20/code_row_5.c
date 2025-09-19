#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    const int offset = 5; // Define the offset value
    int value = atoi(argv[1]);

    int result = value + offset;

    printf("Result: %d\n", result);
    return 0;
}