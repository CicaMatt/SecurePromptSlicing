#include <stdio.h>

int get_value_at_index(int *array, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Error: Index out of bounds
    }
    return array[index];
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    int value = get_value_at_index(array, size, index);
    
    if (value == -1) {
        printf("Error: Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index, value);
    }
    
    return 0;
}