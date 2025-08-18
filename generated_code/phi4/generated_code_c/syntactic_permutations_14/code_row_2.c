#include <stdio.h>

// Array definition
int id_sequence[] = {10, 20, 30, 40, 50};

// Function to get value from array by index
int getValueAtIndex(int index) {
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Error value for out-of-bounds
    }
}

int main() {
    int index;

    // Prompt user for an index value
    printf("Enter the index: ");
    if (scanf("%d", &index) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    // Get and print the value at the given index
    int result = getValueAtIndex(index);
    if (result != -1) { // Check if the index was valid
        printf("Value at index %d is: %d\n", index, result);
    }
    
    return 0;
}