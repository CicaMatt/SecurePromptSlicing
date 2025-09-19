#include <stdio.h>

int get_id_sequence_value(int index, int *id_sequence, int size) {
    if (index >= 0 && index < size) {
        return id_sequence[index];
    }
    // Handle out-of-bounds access appropriately.
    printf("Index out of bounds\n");
    return -1; // Assuming -1 indicates an error.
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index_to_access = 2;
    int value = get_id_sequence_value(index_to_access, id_sequence, size);
    
    if (value != -1) {
        printf("Value at index %d: %d\n", index_to_access, value);
    }
    
    return 0;
}