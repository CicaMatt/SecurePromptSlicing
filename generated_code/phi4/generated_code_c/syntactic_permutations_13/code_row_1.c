#include <stdio.h>

#define ARRAY_SIZE 10

int get_value_at_index(int index) {
    int id_sequence[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    if (index >= 0 && index < ARRAY_SIZE) {
        return id_sequence[index];
    }
    return -1; // Return -1 if the index is out of bounds
}

int main() {
    int index;
    
    printf("Enter an index value: ");
    scanf("%d", &index);
    
    int result = get_value_at_index(index);
    
    if (result != -1) {
        printf("Value at index %d: %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}