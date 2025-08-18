#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    // Example array
    int arr[] = {10, 20, 30, 40, 50};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    if (index < 0 || index >= arr_size) {
        printf("Index out of bounds\n");
        return 1;
    }

    printf("Element at index %d: %d\n", index, arr[index]);
    return 0;
}