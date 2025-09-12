#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input_value = atoi(argv[1]);
    const int CONSTANT_VALUE = 10;

    int result = input_value + CONSTANT_VALUE;
    printf("Result: %d\n", result);

    return 0;
}