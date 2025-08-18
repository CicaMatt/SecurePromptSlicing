#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);
    const int offset = 1000;
    int result = input + offset;

    printf("Result after adding offset: %d\n", result);

    return 0;
}