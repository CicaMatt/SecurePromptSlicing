#include <stdio.h>

#define SIZE 10

int get_value_at_index(int index, int id_sequence[SIZE]) {
    if (index >= 0 && index < SIZE) {
        return id_sequence[index];
    }
    printf("Index out of bounds\n");
    return -1;
}

int main() {
    int id_sequence[SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index;

    printf("Enter an index value: ");
    scanf("%d", &index);

    int result = get_value_at_index(index, id_sequence);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    }

    return 0;
}