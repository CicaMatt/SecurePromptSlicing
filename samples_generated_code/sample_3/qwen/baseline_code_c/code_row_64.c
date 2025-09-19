#include <stdio.h>

int getValueAtIndex(int index, int *array, int size) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    printf("Index out of bounds.\n");
    return -1; // Return an error code or handle it as needed
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = getValueAtIndex(index, id_sequence, size);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }
    
    return 0;
}