#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int arr[] = {10, 20, 30, 40, 50};
    int index = atoi(argv[1]);

    if (index < 0 || index >= sizeof(arr) / sizeof(arr[0])) {
        fprintf(stderr, "Index out of bounds\n");
        return 1;
    }

    printf("Element at index %d is %d\n", index, arr[index]);
    return 0;
}