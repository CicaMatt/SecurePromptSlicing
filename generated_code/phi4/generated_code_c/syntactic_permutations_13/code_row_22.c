#include <stdio.h>

// Function to get the value from an array at a specific index
int getValueAtIndex(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Return an invalid value to indicate error
    }
}

int main() {
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = getValueAtIndex(index);

    if (value != -1) { // Check if the returned value is valid
        printf("Value at index %d: %d\n", index, value);
    }

    return 0;
}