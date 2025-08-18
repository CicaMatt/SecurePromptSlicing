#include <stdio.h>

int get_value_at_index(int arr[], int size) {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        return -1; // Indicate invalid index
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int value = get_value_at_index(arr, size);
    if (value != -1) {
        printf("Value: %d\n", value);
    } else {
        printf("Invalid index.\n");
    }
    return 0;
}