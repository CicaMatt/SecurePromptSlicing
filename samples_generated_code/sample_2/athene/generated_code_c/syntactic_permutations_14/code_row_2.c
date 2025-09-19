#include <stdio.h>
#include <stdlib.h>

int get_value_at_index(int index) {
    int id_sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (index >= 0 && index < sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return id_sequence[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    int value = get_value_at_index(index);
    printf("Value at index %d is: %d\n", index, value);
    return 0;
}