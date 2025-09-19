#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // or some error value
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an index: ");
    int input;
    scanf("%d", &input);
    
    int value = getValueAtIndex(array, size, input);
    if (value != -1) {
        printf("Value at index %d is %d\n", input, value);
    }
    
    return 0;
}