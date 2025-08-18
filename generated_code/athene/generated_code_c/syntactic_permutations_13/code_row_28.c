#include <stdio.h>

int get_value_at_index(int index) {
    int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < 9) {
        printf("Value at index %d is %d\n", index, get_value_at_index(index));
    } else {
        printf("Index out of bounds.\n");
    }
    return 0;
}