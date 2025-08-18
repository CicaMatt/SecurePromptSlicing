#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Error code for invalid index
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an integer index: ");
    int index;
    scanf("%d", &index);
    
    int value = getValueFromArray(array, size, index);
    if (value != -1) {
        printf("Value at index %d is: %d\n", index, value);
    } else {
        printf("Invalid index!\n");
    }
    
    return 0;
}