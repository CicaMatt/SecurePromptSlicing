#include <stdio.h>

int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int get_value_at_index(int index) {
    return id_sequence[index];
}

int main() {
    int index = 3;
    printf("Value at index %d is %d\n", index, get_value_at_index(index));
    return 0;
}