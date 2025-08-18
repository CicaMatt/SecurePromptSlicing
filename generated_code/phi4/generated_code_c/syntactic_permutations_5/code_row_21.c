#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int number = atoi(argv[1]);

    // Create an array of elements with the size equal to the integer input
    int arr[number];

    // Initialize the array elements
    for (int i = 0; i < number; i++) {
        arr[i] = i * i; // Example: storing squares of indices
    }

    // Print the array elements
    printf("Array Elements:\n");
    for (int i = 0; i < number; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}