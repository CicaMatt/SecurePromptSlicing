#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    int addValue = 5; // Example value to add
    int result = value + addValue;

    printf("The result is: %d\n", result);
    return 0;
}