#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array with 10 elements
    int length = sizeof(array) / sizeof(array[0]); // Calculate the number of elements in the array
    int index;
    
    printf("Enter an integer: ");
    scanf("%d", &index);
    
    if (index >= 0 && index < length) {
        printf("Value at index %d is: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds. Please enter a value between 0 and %d.\n", length - 1);
    }
    
    return 0;
}