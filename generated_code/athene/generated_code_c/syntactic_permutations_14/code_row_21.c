#include <stdio.h>

int get_value_at_index(int id_sequence[], int size) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        return id_sequence[index];
    }
    return -1; // Return -1 if the index is out of bounds
}

int main() {
    int id_sequence[] = {1, 2, 3, 4, 5};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int value = get_value_at_index(id_sequence, size);
    printf("Value at index: %d\n", value);
    return 0;
}