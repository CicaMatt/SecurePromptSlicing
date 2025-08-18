#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 for out-of-bounds index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an integer index: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueFromArray(id_sequence, size, index);
    return result;
}