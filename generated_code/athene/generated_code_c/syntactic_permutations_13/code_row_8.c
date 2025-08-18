#include <stdio.h>

int get_value_at_index(int index, int *id_sequence, int length) {
    if (index < 0 || index >= length) return -1;
    return id_sequence[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    int value = get_value_at_index(index, id_sequence, length);
    
    if (value == -1) {
        printf("Index out of bounds.\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}