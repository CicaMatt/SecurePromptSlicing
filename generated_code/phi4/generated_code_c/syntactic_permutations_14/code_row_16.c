#include <stdio.h>

int get_value_at_index(int index, int *id_sequence) {
    if (index >= 0 && index < 10) { // Assuming id_sequence has a maximum size of 10
        return id_sequence[index];
    }
    fprintf(stderr, "Index out of bounds\n");
    return -1; // Return an error code for invalid indices
}

int main() {
    int id_sequence[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Example sequence
    int index;
    
    printf("Enter an index value: ");
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = get_value_at_index(index, id_sequence);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    }

    return 0;
}