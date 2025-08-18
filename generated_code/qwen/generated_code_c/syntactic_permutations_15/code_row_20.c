#include <stdio.h>

int getValueAtIndex(int index, int *array, int size) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return an error code or handle it as needed
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index value: ");
    scanf("%d", &index);

    int result = getValueAtIndex(index, id_sequence, size);
    if (result != -1) {
        printf("The value at index %d is %d.\n", index, result);
    }

    return 0;
}