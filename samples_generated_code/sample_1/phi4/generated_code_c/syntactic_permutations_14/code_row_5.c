#include <stdio.h>

// Define the sequence as a static constant array.
static const int id_sequence[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

// Function to get value at a given index in the array
int get_value_at_index(int index) {
    if (index < 0 || index >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // Or another error code or handling mechanism
    }
    return id_sequence[index];
}

int main() {
    int index = 4;
    int value = get_value_at_index(index);
    
    if (value != -1) { 
        printf("Value at index %d is: %d\n", index, value);
    }

    return 0;
}