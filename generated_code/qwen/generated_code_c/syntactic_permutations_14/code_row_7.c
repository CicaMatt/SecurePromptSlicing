#include <stdio.h>

int get_value_at_index(int id_sequence[], int index) {
    return id_sequence[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int index = 2;
    printf("Value at index %d is %d\n", index, get_value_at_index(id_sequence, index));
    return 0;
}