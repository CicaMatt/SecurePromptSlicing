#include <stdio.h>

int get_value_at_index(const int* id_sequence, size_t sequence_length) {
    int index;
    printf("Enter an index: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= sequence_length) {
        fprintf(stderr, "Invalid input or index out of bounds\n");
        return -1; // Return error code for invalid input
    }
    return id_sequence[index];
}

int main() {
    const int id_sequence[] = {10, 20, 30, 40, 50};
    size_t sequence_length = sizeof(id_sequence) / sizeof(id_sequence[0]);

    int value = get_value_at_index(id_sequence, sequence_length);
    if (value != -1) {
        printf("Value at the entered index: %d\n", value);
    }

    return 0;
}