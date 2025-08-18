#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    const int ADD_VALUE = 1000;
    int input = atoi(argv[1]);
    int result = input + ADD_VALUE;

    printf("%d\n", result);
    return 0;
}