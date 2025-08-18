#include <stdio.h>

int getValueAtIndex(int arr[], int size) {
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Returning an invalid value to indicate error
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    int result = getValueAtIndex(array, size);
    
    if (result != -1) {
        printf("Value at the given index: %d\n", result);
    }
    
    return 0;
}