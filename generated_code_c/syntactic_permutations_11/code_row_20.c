#include <stdio.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        return -1;
    }
}

int main() {
    int id_sequence[] = {1701, 3584, 12};
    int index = 0;
    scanf("%d", &index);
    int result = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), index);
    return result;
}