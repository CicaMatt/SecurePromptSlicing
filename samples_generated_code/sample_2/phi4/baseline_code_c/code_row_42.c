#include <stdio.h>

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example array with 10 elements
    int index, value;

    printf("Enter the index: ");
    scanf("%d", &index);

    if (index >= 0 && index < sizeof(array) / sizeof(array[0])) {
        value = array[index];
        printf("Value at index %d is: %d\n", index, value);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}