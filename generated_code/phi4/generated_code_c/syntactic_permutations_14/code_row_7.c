#include <stdio.h>
#include <stdlib.h>

int get_value_at_index(int *id_sequence, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error code for out-of-bounds access
    }
    return id_sequence[index];
}

int main() {
    int sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(sequence) / sizeof(sequence[0]);
    int index_to_access = 3;
    
    int value = get_value_at_index(sequence, size, index_to_access);
    if (value == -1) {
        printf("Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index_to_access, value);
    }
    
    return 0;
}