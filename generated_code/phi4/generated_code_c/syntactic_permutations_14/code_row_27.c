#include <stdio.h>

int get_value_at_index(int *id_sequence, int size) {
    int index;
    
    printf("Enter index value: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= size) {
        printf("Invalid index.\n");
        return -1; // Return an error code or handle as necessary
    }

    return id_sequence[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int value = get_value_at_index(id_sequence, size);
    if (value != -1) {
        printf("Value at entered index: %d\n", value);
    }

    return 0;
}