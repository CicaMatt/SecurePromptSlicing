#include <stdio.h>

int get_value_at_index(int index, int *array) {
    return array[index];
}

int main() {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index < 0 || index >= size) {
        printf("Index out of bounds.\n");
        return 1;
    }

    int value = get_value_at_index(index, arr);
    printf("Value at index %d is %d\n", index, value);
    return 0;
}