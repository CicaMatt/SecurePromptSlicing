#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    printf("Index out of bounds\n");
    return -1; // Indicate an error for out-of-bounds access
}

int main() {
    int size;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int arr[size];
    
    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int value = getValueAtIndex(arr, size, index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}