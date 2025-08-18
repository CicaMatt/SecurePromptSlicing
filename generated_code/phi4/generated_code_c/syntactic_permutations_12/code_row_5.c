#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an invalid value or handle error as needed
}

int main() {
    int n;
    scanf("%d", &n);

    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);

    int index = n % size; // Ensure the index is within bounds
    int value = getValueFromArray(array, size, index);
    
    return value;
}