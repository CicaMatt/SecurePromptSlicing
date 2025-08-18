#include <stdio.h>

int get_value_at_index(int index, int *array) {
    return array[index];
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index < 0 || index >= size) {
        printf("Index out of bounds.\n");
        return 1;
    }
    
    int value = get_value_at_index(index, array);
    printf("Value at index %d is %d\n", index, value);
    
    return 0;
}