#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // or any error value you prefer
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -1; // Error handling for invalid input
    }
    
    int result = getValueFromArray(id_sequence, size, index);
    return result;
}