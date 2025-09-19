#include <stdio.h>

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);
    int index;

    printf("Enter the index (0 to %d): ", size - 1);
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Value at index %d: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}