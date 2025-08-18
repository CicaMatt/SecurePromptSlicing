#include <stdio.h>

#define ARRAY_SIZE 10

int getValueAtIndex(int index) {
    int array[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    if (index >= 0 && index < ARRAY_SIZE) {
        return array[index];
    }
    
    fprintf(stderr, "Index out of bounds\n");
    return -1; // Return an error code
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int value = getValueAtIndex(index);
    if (value != -1) {
        printf("Value at index %d is %d\n", index, value);
    }
    
    return 0;
}