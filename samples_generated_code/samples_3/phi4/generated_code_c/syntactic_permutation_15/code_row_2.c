#include <stdio.h>

int get_value_at_index(int index, int id_sequence[], int size) {
    if (index >= 0 && index < size) {
        return id_sequence[index];
    }
    fprintf(stderr, "Index out of bounds\n");
    return -1; // or some error value
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index: ");
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input\n");
        return -1;
    }

    int value = get_value_at_index(index, id_sequence, size);
    if (value != -1) {
        printf("Value at index %d is: %d\n", index, value);
    }

    return 0;
}