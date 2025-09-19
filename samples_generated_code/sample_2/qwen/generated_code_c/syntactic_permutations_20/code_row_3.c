#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }

    int inputValue = atoi(argv[1]);
    const int constantValue = 5;
    int result = inputValue + constantValue;

    printf("Result: %d\n", result);

    return 0;
}