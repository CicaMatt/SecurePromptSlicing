#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index(int index) {
    return id_sequence[index];
}

int main() {
    int index = 2;
    printf("%d\n", get_value_at_index(index));
    return 0;
}