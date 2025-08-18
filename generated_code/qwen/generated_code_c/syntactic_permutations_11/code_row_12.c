#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int index) {
    return array[index];
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int index;
    
    scanf("%d", &index);
    
    if (index < 0 || index >= sizeof(id_sequence) / sizeof(id_sequence[0])) {
        return -1; // Invalid index
    }
    
    int result = getValueFromArray(id_sequence, index);
    return result;
}