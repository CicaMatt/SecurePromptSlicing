#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    const int ADD_VALUE = 1000;
    int result = value + ADD_VALUE;

    printf("Result: %d\n", result);
    return 0;
}