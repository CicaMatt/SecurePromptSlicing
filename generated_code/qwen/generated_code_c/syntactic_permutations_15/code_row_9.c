#include <stdio.h>

int getValueAtIndex(int index, int *array, int size) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return a sentinel value indicating an error
    }
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int dex;

    printf("Enter the index: ");
    scanf("%d", &dex);

    int value = getValueAtIndex(dex, id_sequence, size);
    if (value != -1) {
        printf("The value at index %d is %d.\n", dex, value);
    }

    return 0;
}