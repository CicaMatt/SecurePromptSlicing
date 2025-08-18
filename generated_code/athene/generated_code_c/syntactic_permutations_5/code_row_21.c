#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);

    if (num >= 0 && num < size) {
        printf("Element at index %d is %d\n", num, array[num]);
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    return 0;
}