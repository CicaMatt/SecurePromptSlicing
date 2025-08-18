#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int index = atoi(argv[1]);
    int elements[] = {10, 20, 30, 40, 50};
    int size = sizeof(elements) / sizeof(elements[0]);

    if (index < 0 || index >= size) {
        return 1;
    }

    printf("%d\n", elements[index]);
    return 0;
}