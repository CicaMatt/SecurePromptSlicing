#include <stdio.h>

int getValueAtIndex(int index) {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        printf("Index out of bounds.\n");
        return -1;
    }
}

int main() {
    int index, value;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    value = getValueAtIndex(index);
    
    if (value != -1) {
        printf("The value at index %d is %d.\n", index, value);
    }
    
    return 0;
}