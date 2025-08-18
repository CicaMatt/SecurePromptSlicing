#include <stdio.h>

#define ARRAY_SIZE 10

// Function prototype declaration
int getValueAtIndex(int index);

int main() {
    int index;
    printf("Enter an index value (0 to %d): ", ARRAY_SIZE - 1);
    scanf("%d", &index);

    int value = getValueAtIndex(index);

    if (value != -1) {
        printf("Value at index %d: %d\n", index, value);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}

// Function to get the value at a given index in id_sequence
int getValueAtIndex(int index) {
    int id_sequence[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    if (index >= 0 && index < ARRAY_SIZE) {
        return id_sequence[index];
    } else {
        return -1; // Return an error code for out of bounds
    }
}