#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // Handle invalid index
    printf("Index out of bounds\n");
    return -1; // Return an error value or handle as needed
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    
    printf("Enter the index: ");
    scanf("%d", &index);

    int value = getValueAtIndex(array, size, index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }

    return 0;
}