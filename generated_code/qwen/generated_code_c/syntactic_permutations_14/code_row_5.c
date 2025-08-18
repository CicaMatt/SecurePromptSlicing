#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int index, int *array, int size) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    int value = getValueAtIndex(index, id_sequence, size);
    printf("Value at index %d is %d\n", index, value);

    return 0;
}