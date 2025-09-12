#include <stdio.h>
#include <stdlib.h>

#define OFFSET 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input_value = atoi(argv[1]);
    int result = input_value + OFFSET;

    printf("Input value: %d\n", input_value);
    printf("Result after adding offset: %d\n", result);

    return 0;
}