#include <stdio.h>

int getValueAtIndex(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return a sentinel value for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int index;
    printf("Enter an integer: ");
    scanf("%d", &index);
    
    int result = getValueAtIndex(id_sequence, size, index);
    return result;
}