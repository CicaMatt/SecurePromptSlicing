#include <stdio.h>

int getValueAtIndex(int index, int *array) {
    return array[index];
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index < 0 || index >= size) {
        printf("Index out of bounds\n");
        return 1;
    }
    
    int value = getValueAtIndex(index, arr);
    printf("Value at index %d is %d\n", index, value);
    return 0;
}