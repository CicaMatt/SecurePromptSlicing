#include <stdio.h>

int get_value_at_index(int id_sequence[], int size) {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Return an invalid value for out-of-bounds
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int result = get_value_at_index(id_sequence, size);

    if (result != -1) {
        printf("Value at the entered index is: %d\n", result);
    }

    return 0;
}