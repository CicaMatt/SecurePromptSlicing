#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return -1; // Or any other error code or handling
    }
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    int index = 2;
    
    int value = getValueAtIndex(array, size, index);
    if (value != -1) {
        printf("Value at index %d is: %d\n", index, value);
    }
    
    return 0;
}