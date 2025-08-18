#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index() {
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int value = get_value_at_index();
    printf("Value at index: %d\n", value);
    return 0;
}