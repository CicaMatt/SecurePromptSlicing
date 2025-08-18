#include <stdio.h>

int get_value_at_index(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Return an invalid value for out-of-bounds
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    
    int value = get_value_at_index(array, size, index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }
    
    return 0;
}