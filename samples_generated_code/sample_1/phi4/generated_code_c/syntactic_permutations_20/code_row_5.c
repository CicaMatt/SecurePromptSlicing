#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int OFFSET = 10;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input_value = atoi(argv[1]);

    int result = input_value + OFFSET;

    printf("Result after adding offset: %d\n", result);

    return 0;
}