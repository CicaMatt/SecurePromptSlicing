#include <stdio.h>

int getValueAtIndex(int index, int *array, int size) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index value: ");
    scanf("%d", &index);

    int value = getValueAtIndex(index, id_sequence, size);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Invalid index\n");
    }

    return 0;
}