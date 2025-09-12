#include <stdio.h>

int get_value_at_index(int index, int *array, int size) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Error or out of bounds
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = get_value_at_index(index, arr, size);
    
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}