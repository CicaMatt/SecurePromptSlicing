#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);
    const int constant = 5;
    int result = input + constant;

    printf("The result is: %d\n", result);
    return 0;
}