#include <stdio.h>
#include <stdlib.h>

int get_value_at_index(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1;
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;
    scanf("%d", &index);
    int result = get_value_at_index(id_sequence, size, index);
    return result;
}