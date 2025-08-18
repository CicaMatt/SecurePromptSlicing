#include <stdio.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // or any error indicator
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an index: ");
    int index;
    scanf("%d", &index);
    
    int value = getValueFromArray(array, size, index);
    if (value == -1) {
        fprintf(stderr, "Invalid index\n");
        return 1; // or any error code
    }
    
    printf("Value at given index: %d\n", value);
    return value;
}