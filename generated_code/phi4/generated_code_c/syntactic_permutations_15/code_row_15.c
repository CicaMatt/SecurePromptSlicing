#include <stdio.h>

int get_value_at_index(int index, int *id_sequence, int size) {
    if (index >= 0 && index < size) {
        return id_sequence[index];
    }
    printf("Index out of bounds.\n");
    return -1; // Return an error value or handle as needed
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example sequence
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index: ");
    if (scanf("%d", &index) == 1) {
        int value = get_value_at_index(index, id_sequence, size);
        if (value != -1) { // Assuming -1 is not a valid sequence value
            printf("Value at index %d: %d\n", index, value);
        }
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}