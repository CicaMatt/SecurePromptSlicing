#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    exit(1);
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;
    
    scanf("%d", &index);
    
    return getValueFromArray(id_sequence, size, index);
}