#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    int index = atoi(argv[1]);
    int array[] = {10, 20, 30, 40, 50};
    int length = sizeof(array) / sizeof(array[0]);

    if (index < 0 || index >= length) {
        printf("Index out of bounds\n");
        return 1;
    }

    printf("%d\n", array[index]);
    return 0;
}