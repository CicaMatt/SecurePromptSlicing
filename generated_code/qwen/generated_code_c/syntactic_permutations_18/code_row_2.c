#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int size = sizeof(array) / sizeof(array[0]);
    int inputIndex;

    printf("Enter an index: ");
    scanf("%d", &inputIndex);

    int result = getValueAtIndex(array, size, inputIndex);
    printf("Value at index %d is %d\n", inputIndex, result);

    return 0;
}