#include <stdio.h>

#define SIZE 10

int get_value_at_index(int index, int id_sequence[SIZE]);

int main() {
    int id_sequence[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index;

    printf("Enter an index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < SIZE) {
        int value = get_value_at_index(index, id_sequence);
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}

int get_value_at_index(int index, int id_sequence[SIZE]) {
    return id_sequence[index];
}