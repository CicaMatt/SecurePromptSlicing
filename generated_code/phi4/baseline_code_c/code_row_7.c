#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Usage: %s <index> <number>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index < 1 || index >= argc) {
        printf("Index out of range.\n");
        return 1;
    }

    char *targetArg = argv[index];
    printf("%s\n", targetArg);

    return 0;
}