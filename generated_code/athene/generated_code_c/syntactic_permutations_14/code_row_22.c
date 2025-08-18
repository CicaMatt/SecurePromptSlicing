#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index(int index) {
    return id_sequence[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < 5) {
        int value = get_value_at_index(index);
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds.\n");
    }
    return 0;
}