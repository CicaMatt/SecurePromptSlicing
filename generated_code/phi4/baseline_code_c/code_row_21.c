#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    value += 1000;

    printf("Value after adding 1000: %d\n", value);

    return 0;
}