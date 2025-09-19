#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Indicate error with a value outside the expected range of input
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size_of_array = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        exit(EXIT_FAILURE); // Exit if input is not valid
    }

    int result = getValueFromArray(id_sequence, size_of_array, index);
    return result; // Return value as the program's exit code
}