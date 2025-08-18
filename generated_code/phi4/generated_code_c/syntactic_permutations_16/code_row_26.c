#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // or any sentinel value indicating error
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an integer index: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueAtIndex(array, size, index);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    }
    
    return 0;
}