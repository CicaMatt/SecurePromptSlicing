#include <stdio.h>

int get_value_at_index(int arr[], int size) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        return -1; // Error code for invalid index
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int value = get_value_at_index(array, size);
    if (value != -1) {
        printf("Value: %d\n", value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}