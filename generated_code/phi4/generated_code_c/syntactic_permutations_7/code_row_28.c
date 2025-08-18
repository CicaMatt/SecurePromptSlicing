#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <index> <arg_index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index + 1 >= argc) {
        printf("Argument at position %d is out of range.\n", index);
        return 1;
    }

    printf("%s\n", argv[index + 1]);

    return 0;
}