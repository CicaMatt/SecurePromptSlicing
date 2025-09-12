#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    const int SIZE = sizeof(arr) / sizeof(arr[0]);
    
    printf("Enter an integer index: ");
    int index;
    scanf("%d", &index);
    
    if (index >= 0 && index < SIZE) {
        printf("The value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds. Please enter a number between 0 and %d.\n", SIZE - 1);
    }
    
    return 0;
}