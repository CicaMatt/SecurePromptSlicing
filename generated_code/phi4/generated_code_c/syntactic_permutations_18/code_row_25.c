#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Value at index %d is: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds!\n");
    }

    return 0;
}