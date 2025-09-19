#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("No index provided.\n");
        return 1;
    }

    int index = atoi(argv[1]);
    if (index < 0 || index >= argc - 1) {
        printf("Index out of range.\n");
        return 1;
    }

    printf("%s\n", argv[index + 1]);
    return 0;
}