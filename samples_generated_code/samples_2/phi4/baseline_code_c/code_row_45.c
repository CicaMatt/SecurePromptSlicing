#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return a default value or handle error as needed
}

int main() {
    int n;
    scanf("%d", &n);

    int array[] = {1, 2, 3, 4, 5}; // Example array
    int size = sizeof(array) / sizeof(array[0]);

    if (n < 0 || n >= size) {
        printf("Index out of bounds\n");
        return -1;
    }

    int value = getValueFromArray(array, size, n);
    printf("%d\n", value);

    return value;
}