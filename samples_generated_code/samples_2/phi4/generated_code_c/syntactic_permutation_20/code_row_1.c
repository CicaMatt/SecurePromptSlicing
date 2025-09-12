#include <stdio.h>
#include <stdlib.h>

#define OFFSET 5

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);
    int result = input + OFFSET;

    printf("Result after adding offset: %d\n", result);

    return 0;
}