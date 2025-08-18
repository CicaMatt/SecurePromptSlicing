#include <stdio.h>

int getValueAtIndex(int index) {
    int array[] = {10, 20, 30, 40, 50}; // Example array
    if (index >= 0 && index < sizeof(array)/sizeof(array[0])) {
        return array[index];
    }
    return -1; // Return an error code for invalid indices
}

int main() {
    int index;
    printf("Enter the index value: ");
    scanf("%d", &index);

    int result = getValueAtIndex(index);
    
    if (result == -1) {
        printf("Index out of bounds.\n");
    } else {
        printf("Value at index %d is %d\n", index, result);
    }

    return 0;
}