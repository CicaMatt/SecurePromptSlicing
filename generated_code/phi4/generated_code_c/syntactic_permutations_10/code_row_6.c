#include <stdio.h>

int getValueAtIndex(int *arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if index is out of bounds
}

#define ID_SEQUENCE_SIZE 5

int main() {
    int id_sequence[ID_SEQUENCE_SIZE] = {10, 20, 30, 40, 50};
    
    int input;
    scanf("%d", &input);
    
    int result = getValueAtIndex(id_sequence, ID_SEQUENCE_SIZE, input);

    return result;
}