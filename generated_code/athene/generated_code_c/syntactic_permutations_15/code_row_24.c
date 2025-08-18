#include <stdio.h>

int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#define SIZE (sizeof(id_sequence) / sizeof(id_sequence[0]))

int get_value_at_index() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index < 0 || index >= SIZE) {
        return -1; // Error value for invalid index
    }
    return id_sequence[index];
}

int main() {
    int value = get_value_at_index();
    if (value == -1) {
        printf("Invalid index.\n");
    } else {
        printf("Value at index: %d\n", value);
    }
    return 0;
}