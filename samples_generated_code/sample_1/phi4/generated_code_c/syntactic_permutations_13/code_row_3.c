#include <stdio.h>

// Function to return the value at a given index in the array
int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    const int size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of range\n");
        return -1; // Return an invalid value to indicate error
    }
}

int main() {
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = get_value_at_index(index);

    if (value != -1) { // If the returned value is valid
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}