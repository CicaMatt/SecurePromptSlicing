#include <stdio.h>

int getValueAtIndex(int *array, int length, int index) {
    if (index < 0 || index >= length) {
        return -1; // Return -1 for invalid index
    }
    return array[index];
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int length = sizeof(array) / sizeof(array[0]);
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int value = getValueAtIndex(array, length, index);
    if (value == -1) {
        printf("Invalid index\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    
    return 0;
}