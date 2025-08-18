#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1;
}

int main() {
    int size, index;
    scanf("%d %d", &size, &index);
    int array[size];
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    int value = getValueFromArray(array, size, index);
    return value;
}