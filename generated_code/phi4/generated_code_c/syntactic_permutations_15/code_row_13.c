#include <stdio.h>

int get_value_at_index() {
    int index;
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Return a sentinel value for error
    }
}

int main() {
    int result = get_value_at_index();
    
    if (result != -1) {
        printf("Value at given index: %d\n", result);
    }

    return 0;
}