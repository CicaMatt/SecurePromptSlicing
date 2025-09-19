#include <stdio.h>

int get_value_at_index(int index, int arr[], int size) {
    if (index < 0 || index >= size) {
        return -1; // Error or out-of-bounds indicator
    }
    return arr[index];
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    scanf("%d", &index);
    int value = get_value_at_index(index, array, size);
    if (value == -1) {
        printf("Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}