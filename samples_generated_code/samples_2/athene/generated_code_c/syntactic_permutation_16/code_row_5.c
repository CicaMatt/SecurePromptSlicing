#include <stdio.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error code for invalid index
    }
    return array[index];
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int value = getValueAtIndex(array, size, index);
    
    if (value == -1) {
        printf("Invalid index.\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    
    return 0;
}