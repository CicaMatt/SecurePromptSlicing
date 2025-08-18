#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter the index: ");
    int index;
    scanf("%d", &index);

    int value = getValueAtIndex(array, size, index);
    printf("Value at index %d is: %d\n", index, value);

    return 0;
}