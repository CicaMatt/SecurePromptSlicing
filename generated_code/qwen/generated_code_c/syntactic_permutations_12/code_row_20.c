#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return -1 for invalid index
}

int main() {
    int size;
    scanf("%d", &size);
    int *array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    int index;
    scanf("%d", &index);
    int result = getValueFromArray(array, size, index);
    free(array);
    return result;
}