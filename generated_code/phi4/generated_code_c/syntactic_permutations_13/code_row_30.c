#include <stdio.h>

int getValueAtIndex(int index) {
    int array[] = {10, 20, 30, 40, 50};
    if (index >= 0 && index < sizeof(array)/sizeof(array[0])) {
        return array[index];
    } else {
        printf("Index out of bounds\n");
        return -1; // Return an invalid value to indicate error
    }
}

int main() {
    int index;
    printf("Enter the index value: ");
    scanf("%d", &index);
    
    int result = getValueAtIndex(index);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    }

    return 0;
}