#include <stdio.h>

// Define the array
int id_sequence[] = {10, 20, 30, 40, 50};

// Function to get value from id_sequence by index
int getValueAtIndex(int index) {
    if (index >= 0 && index < sizeof(id_sequence)/sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    printf("Index out of bounds\n");
    return -1; // Return an error code for out-of-bounds access
}

int main() {
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = getValueAtIndex(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }
    
    return 0;
}