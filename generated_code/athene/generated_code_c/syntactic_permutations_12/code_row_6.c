#include <stdio.h>
#include <stdlib.h>

int get_value_at_index(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1;
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int index;
    scanf("%d", &index);
    int value = get_value_at_index(array, size, index);
    return value;
}