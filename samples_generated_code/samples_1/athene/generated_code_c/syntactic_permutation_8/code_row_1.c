#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <index> <arg1> [<arg2> ...]\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    if (index < 0 || index >= argc - 1) {
        printf("Index out of bounds\n");
        return 1;
    }

    printf("%s\n", argv[index + 2]);
    return 0;
}