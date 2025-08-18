#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    printf("Index out of bounds!\n");
    return -1;
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    int value = getValueAtIndex(id_sequence, size, index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}