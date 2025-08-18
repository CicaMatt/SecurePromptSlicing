#include <stdio.h>

int get_value_at_index(int *id_sequence, int length) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < length) {
        return id_sequence[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int id_sequence[] = {1, 2, 3, 4, 5};
    int length = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int value = get_value_at_index(id_sequence, length);
    if (value != -1) {
        printf("Value: %d\n", value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}