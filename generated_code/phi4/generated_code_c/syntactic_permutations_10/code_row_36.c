#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return a value that indicates an out-of-bounds access
}

int main() {
    int id_sequence[ARRAY_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    printf("Enter the index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        exit(EXIT_FAILURE); // Exit if input is not an integer
    }

    int result = getValueFromArray(id_sequence, ARRAY_SIZE, index);
    return result;
}