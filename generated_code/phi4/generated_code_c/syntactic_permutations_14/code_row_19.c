#include <stdio.h>

int getValueAt(int index, int id_sequence[], int size) {
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicate error with an invalid value
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = getValueAt(index, id_sequence, size);
    
    if (value != -1) {
        printf("Value at index %d is: %d\n", index, value);
    }
    
    return 0;
}