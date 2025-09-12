#include <stdio.h>

int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#define ARRAY_SIZE 10

int get_value_at_index() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < ARRAY_SIZE) {
        return id_sequence[index];
    } else {
        return -1; // Indicate invalid index
    }
}

int main() {
    int value = get_value_at_index();
    if (value != -1) {
        printf("Value at index: %d\n", value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}