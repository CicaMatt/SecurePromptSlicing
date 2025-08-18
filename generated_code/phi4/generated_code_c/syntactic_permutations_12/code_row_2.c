#include <stdio.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error value if index is out of bounds
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter the index: ");
    int index;
    scanf("%d", &index);
    
    int value = getValueFromArray(array, size, index);
    return value;
}