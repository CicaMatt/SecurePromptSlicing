#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value for out-of-bounds access
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index: ");
    if (scanf("%d", &size) == 1 && size >= 0 && size < sizeof(id_sequence)/sizeof(int)) {
        exit(getValueFromArray(id_sequence, size, size));
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
}