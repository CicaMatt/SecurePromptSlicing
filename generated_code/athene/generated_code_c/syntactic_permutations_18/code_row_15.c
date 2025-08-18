#include <stdio.h>

int get_value_at_index(int index, int *array) {
    return array[index];
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int size = sizeof(array) / sizeof(array[0]);
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    if (index < 0 || index >= size) {
        printf("Index out of bounds.\n");
    } else {
        int value = get_value_at_index(index, array);
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}