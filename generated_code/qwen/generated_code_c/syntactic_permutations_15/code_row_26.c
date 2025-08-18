#include <stdio.h>

int getValueAtIndex(int *array, int size) {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Return a special value to indicate an error
    }
}

int main() {
    int myArray[] = {10, 20, 30, 40, 50};
    int size = sizeof(myArray) / sizeof(myArray[0]);

    int result = getValueAtIndex(myArray, size);
    if (result != -1) {
        printf("Value at index: %d\n", result);
    }

    return 0;
}