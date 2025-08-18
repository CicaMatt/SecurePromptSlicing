#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1;
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;

    if (scanf("%d", &index) != 1) {
        return -1;
    }

    int result = getValueAtIndex(id_sequence, size, index);
    return result;
}