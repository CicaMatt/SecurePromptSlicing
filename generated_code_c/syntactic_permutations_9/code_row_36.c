#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s index\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index <= 0 || index >= argc) {
        printf("Index out of range.\n");
        return 1;
    }

    char *arg = argv[index];

    printf("%s\n", arg);
    return 0;
}