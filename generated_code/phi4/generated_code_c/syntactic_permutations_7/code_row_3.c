#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <index> <string_to_print>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index < 2 || index >= argc) {
        printf("Index out of range. Please provide a valid index.\n");
        return 1;
    }

    printf("%s\n", argv[index]);

    return 0;
}