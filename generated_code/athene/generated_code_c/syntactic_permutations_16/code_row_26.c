#include <stdio.h>

int getValueAtIndex(int index, int arr[], int size) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 if index is out of bounds
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int value = getValueAtIndex(index, array, size);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}