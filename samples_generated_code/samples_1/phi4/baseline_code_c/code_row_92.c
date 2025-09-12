#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1;
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size_of_array = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    int input_index;
    if (scanf("%d", &input_index) != 1) {
        return -1;
    }
    
    int result = getValueFromArray(id_sequence, size_of_array, input_index);
    return result;
}