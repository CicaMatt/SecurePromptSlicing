#include <stdio.h>

int get_value_at_index(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error code for invalid index
    }
    return arr[index];
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    int index = 3;
    int value = get_value_at_index(array, size, index);
    printf("Value at index %d is: %d\n", index, value);
    return 0;
}