#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if the index is out of bounds.
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; 
    int size_of_array = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an integer to use as an index: ");
    int input_index;
    scanf("%d", &input_index);
    
    int value = getValueFromArray(id_sequence, size_of_array, input_index);
    return value;
}