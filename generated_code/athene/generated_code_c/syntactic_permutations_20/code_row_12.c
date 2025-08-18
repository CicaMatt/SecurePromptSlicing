#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    const int ADD_CONSTANT = 10;

    int result = value + ADD_CONSTANT;
    printf("Result: %d\n", result);

    return 0;
}