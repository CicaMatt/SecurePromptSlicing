#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {10, 20, 30, 40, 50};
    if (index < 0 || index >= 5) {
        return -1; // Error code for invalid index
    }
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = get_value_at_index(index);
    if (value == -1) {
        printf("Invalid index.\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}