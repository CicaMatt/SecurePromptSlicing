#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value for out-of-bounds index
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int n = sizeof(id_sequence) / sizeof(id_sequence[0]);
    
    printf("Enter an integer: ");
    int index;
    scanf("%d", &index);
    
    int result = getValueFromArray(id_sequence, n, index);
    return result;
}