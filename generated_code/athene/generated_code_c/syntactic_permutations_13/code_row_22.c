#include <stdio.h>

int get_value_at_index(int *id_sequence, int index) {
    return id_sequence[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        int value = get_value_at_index(id_sequence, index);
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}