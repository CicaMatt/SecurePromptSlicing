#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input_value = atoi(argv[1]);
    const int constant_value = 10; // Change this value as needed

    int result = input_value + constant_value;

    printf("Result: %d\n", result);
    return 0;
}