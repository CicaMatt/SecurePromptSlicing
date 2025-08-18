#include <stdio.h>

#define ARRAY_SIZE 10

int get_value_at_index(int index, int id_sequence[]) {
    if (index >= 0 && index < ARRAY_SIZE) {
        return id_sequence[index];
    }
    // Optionally handle out-of-bounds by returning a sentinel value or error code.
    printf("Index out of bounds\n");
    return -1; // Return an invalid value for out-of-bounds
}

int main() {
    int id_sequence[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index = 4;
    int result = get_value_at_index(index, id_sequence);
    
    if (result != -1) {
        printf("Value at index %d: %d\n", index, result);
    }

    return 0;
}