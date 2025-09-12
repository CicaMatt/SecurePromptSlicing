#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Define the array
    int arr[] = {10, 20, 30, 40, 50};

    // Check if the index is within bounds
    if (index < 0 || index >= sizeof(arr) / sizeof(arr[0])) {
        printf("Index out of bounds\n");
        return 1;
    }

    // Print the element at the given index
    printf("Element at index %d: %d\n", index, arr[index]);

    return 0;
}