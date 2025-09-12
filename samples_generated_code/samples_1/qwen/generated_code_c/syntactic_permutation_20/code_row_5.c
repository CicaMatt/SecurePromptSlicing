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

    printf("Result after adding offset: %d\n", result);

    return 0;
}