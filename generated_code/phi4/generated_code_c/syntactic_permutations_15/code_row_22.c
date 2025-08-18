#include <stdio.h>

int get_value_at_index() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example sequence
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // Returning an error value
    }
}

int main() {
    int result = get_value_at_index();
    if (result != -1) {
        printf("Value at the given index: %d\n", result);
    }
    return 0;
}