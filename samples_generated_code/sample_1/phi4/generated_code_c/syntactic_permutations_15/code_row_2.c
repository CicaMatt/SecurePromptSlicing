#include <stdio.h>

int get_value_at_index(int index, int id_sequence[], int size);

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        int value = get_value_at_index(index, id_sequence, size);
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}

int get_value_at_index(int index, int id_sequence[], int size) {
    if (index >= 0 && index < size) {
        return id_sequence[index];
    }
    return -1; // Return an error value for invalid indices
}