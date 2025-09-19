#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        // If index is out of bounds, return an error code or handle as needed.
        return -1; // Assuming -1 indicates an invalid access
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -2; // Error code for invalid input
    }

    int result = getValueFromArray(id_sequence, size, index);
    exit(result);
}