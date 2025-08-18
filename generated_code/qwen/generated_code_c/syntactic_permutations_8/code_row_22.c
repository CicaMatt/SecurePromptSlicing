#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <index> <string>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index >= argc - 2 || index < 0) {
        printf("Index out of range.\n");
        return 1;
    }

    printf("%s\n", argv[index + 2]);

    return 0;
}