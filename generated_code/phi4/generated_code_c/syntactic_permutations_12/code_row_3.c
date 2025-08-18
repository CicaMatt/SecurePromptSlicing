#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error code if the index is out of bounds.
}

int main() {
    int n;
    scanf("%d", &n);

    int array[100]; // Assuming a maximum size for simplicity
    int i;

    for (i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }

    int index;
    scanf("%d", &index);

    int result = getValueFromArray(array, n, index);
    
    return result;
}