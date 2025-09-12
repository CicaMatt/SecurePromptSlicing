#include <stdio.h>

int get_value_at_index(int index, int id_sequence[], int size) {
    return id_sequence[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    
    printf("Enter an index value: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        int result = get_value_at_index(index, id_sequence, size);
        printf("Value at index %d is: %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}