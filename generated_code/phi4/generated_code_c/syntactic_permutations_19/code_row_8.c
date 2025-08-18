#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    printf("Result: %d\n", num + 1000);

    return 0;
}