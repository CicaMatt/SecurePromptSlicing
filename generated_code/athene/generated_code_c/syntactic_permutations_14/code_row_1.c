#include <stdio.h>

int get_value_at_index(int *id_sequence, int size) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        return id_sequence[index];
    }
    return -1; // Indicate invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int value = get_value_at_index(id_sequence, size);
    if (value != -1) {
        printf("Value: %d\n", value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}