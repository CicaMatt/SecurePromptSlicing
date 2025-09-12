#include <stdio.h>

int get_value_at_index(int index, int arr[]) {
    static const int size = 10;
    static int default_arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (index < 0 || index >= size) return -1; // Out of bounds
    arr = default_arr;
    return arr[index];
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    int value = get_value_at_index(index, NULL);
    if (value == -1) {
        printf("Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    return 0;
}