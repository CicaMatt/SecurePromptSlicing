#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    const int offset = 5; // Example constant offset
    int result = value + offset;

    printf("The result of adding the offset is: %d\n", result);
    return 0;
}