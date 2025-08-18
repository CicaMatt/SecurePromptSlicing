#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <index> <value>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    
    if (index < 1 || index >= argc - 1) {
        printf("Index out of range.\n");
        return 1;
    }

    printf("Value at index %d: %s\n", index, argv[index + 1]);

    return 0;
}