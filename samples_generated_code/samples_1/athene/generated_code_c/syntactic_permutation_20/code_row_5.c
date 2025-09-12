#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <value>\n", argv[0]);
        return 1;
    }

    const int offset = 5;
    int value = atoi(argv[1]);

    printf("%d\n", value + offset);

    return 0;
}