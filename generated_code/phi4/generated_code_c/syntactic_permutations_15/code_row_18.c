#include <stdio.h>

int getValueAtIndex(int index, int id_sequence[], int size) {
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Error code for out-of-bounds
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter the index: ");
    int index;
    scanf("%d", &index);
    
    int value = getValueAtIndex(index, id_sequence, size);
    
    if (value != -1) {
        printf("Value at index %d is: %d\n", index, value);
    }
    
    return 0;
}