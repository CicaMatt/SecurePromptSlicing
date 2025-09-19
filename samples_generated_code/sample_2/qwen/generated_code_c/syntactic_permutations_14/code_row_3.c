#include <stdio.h>

int getValueAtIndex(int index, int *array, int size) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return -1 to indicate an error
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter the index value: ");
    scanf("%d", &index);

    int result = getValueAtIndex(index, id_sequence, size);
    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    }

    return 0;
}