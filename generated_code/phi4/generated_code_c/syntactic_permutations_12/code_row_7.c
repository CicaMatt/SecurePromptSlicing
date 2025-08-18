#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error value if the index is out of bounds
}

int main() {
    int n;
    scanf("%d", &n);

    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);

    int result = getValueFromArray(array, size, n);
    
    exit(result);
}