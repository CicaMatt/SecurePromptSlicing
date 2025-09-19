#include <stdio.h>
#include <stdlib.h>

#define OFFSET 5

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    int result = value + OFFSET;

    printf("Input value: %d\n", value);
    printf("Value with offset: %d\n", result);

    return 0;
}