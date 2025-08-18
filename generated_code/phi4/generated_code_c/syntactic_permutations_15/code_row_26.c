#include <stdio.h>

#define ARRAY_SIZE 10

void printValueAtIndex(int arr[], int size) {
    int index;
    
    printf("Enter an index value: ");
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("The value at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds.\n");
    }
}

int main() {
    int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    printValueAtIndex(array, ARRAY_SIZE);
    
    return 0;
}