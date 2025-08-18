#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if index is out of bounds
}

#define ID_SEQUENCE_SIZE 5

int main() {
    int id_sequence[ID_SEQUENCE_SIZE] = {10, 20, 30, 40, 50};
    
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    
    int result = getValueFromArray(id_sequence, ID_SEQUENCE_SIZE, index);
    return result;
}