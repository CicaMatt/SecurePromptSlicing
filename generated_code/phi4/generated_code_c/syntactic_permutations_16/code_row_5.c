#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // or handle error as needed
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60};
    int size = sizeof(array) / sizeof(array[0]);
    
    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int value = getValueAtIndex(array, size, index);
    
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}