#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int sequence_length = sizeof(id_sequence) / sizeof(id_sequence[0]);

    if (index >= 0 && index < sequence_length) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return an error code or handle it as needed
    }
}

int main() {
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);

    int value = get_value_at_index(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}