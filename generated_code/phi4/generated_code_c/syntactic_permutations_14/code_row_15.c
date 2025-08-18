#include <stdio.h>

int get_value_at_index(const int *id_sequence, size_t length) {
    size_t index;
    printf("Enter an index: ");
    scanf("%zu", &index);

    if (index >= 0 && index < length) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // Error code for invalid index
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(id_sequence) / sizeof(id_sequence[0]);

    int value = get_value_at_index(id_sequence, length);
    if (value != -1) {
        printf("Value at index: %d\n", value);
    }

    return 0;
}