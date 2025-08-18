#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return a sentinel value for invalid index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int size_of_array = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int input_index;
    printf("Enter an integer: ");
    scanf("%d", &input_index);
    
    int result = getValueFromArray(id_sequence, size_of_array, input_index);
    return result; // Exit with the value obtained from getValueFromArray as exit code
}