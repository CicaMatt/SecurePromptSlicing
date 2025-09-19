#include <stdio.h>

int get_value_at_index() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Assuming -1 indicates an error
    }
}

int main() {
    int value = get_value_at_index();
    if (value != -1) {
        printf("Value at the given index: %d\n", value);
    }
    return 0;
}