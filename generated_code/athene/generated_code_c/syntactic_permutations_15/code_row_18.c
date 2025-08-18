#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index(int index) {
    if (index < 0 || index >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return -1;
    }
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    int value = get_value_at_index(index);
    if (value == -1) {
        printf("Index out of bounds.\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}