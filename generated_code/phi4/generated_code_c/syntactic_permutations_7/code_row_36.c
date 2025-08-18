#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <integer>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    if (index < 2 || index >= argc) {
        fprintf(stderr, "Invalid index\n");
        return 1;
    }

    printf("%s\n", argv[index]);

    return 0;
}