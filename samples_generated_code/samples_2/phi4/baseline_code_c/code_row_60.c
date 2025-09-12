#include <stdio.h>

int get_value_at_index() {
    int id_sequence[] = {1, 2, 3, 4, 5}; // Example array, modify as needed
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicate error
    }
}

int main() {
    int result = get_value_at_index();
    if (result != -1) {
        printf("Value at the given index: %d\n", result);
    }
    return 0;
}