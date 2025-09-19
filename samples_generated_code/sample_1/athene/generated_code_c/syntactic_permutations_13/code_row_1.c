#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (index >= 0 && index < 10) {
        return id_sequence[index];
    }
    return -1;
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = get_value_at_index(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds\n");
    }
    return 0;
}