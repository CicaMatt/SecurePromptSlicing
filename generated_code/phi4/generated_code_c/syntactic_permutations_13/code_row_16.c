#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error code if index is out of bounds
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter the index value: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueAtIndex(array, size, index);

    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}