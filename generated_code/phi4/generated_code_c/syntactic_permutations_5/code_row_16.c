#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Define an array with some elements
    int arr[] = {10, 20, 30, 40, 50};

    if (index >= 0 && index < sizeof(arr) / sizeof(arr[0])) {
        printf("Element at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}