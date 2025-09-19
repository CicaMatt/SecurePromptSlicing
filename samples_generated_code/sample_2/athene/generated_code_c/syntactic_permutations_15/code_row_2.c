#include <stdio.h>

int id_sequence[] = {10, 20, 30, 40, 50};

int get_value_at_index() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    return id_sequence[index];
}

int main() {
    int value = get_value_at_index();
    printf("Value at index: %d\n", value);
    return 0;
}