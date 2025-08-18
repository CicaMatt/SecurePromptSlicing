#include <stdio.h>

int get_value_at_index() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size_of_array = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < size_of_array) {
        return id_sequence[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Indicate an error
    }
}

int main() {
    int value = get_value_at_index();
    if (value != -1) {
        printf("Value at the given index: %d\n", value);
    }
    return 0;
}