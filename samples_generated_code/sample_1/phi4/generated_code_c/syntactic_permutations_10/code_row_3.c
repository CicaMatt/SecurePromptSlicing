#include <stdio.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return -1 or some error value if the index is out of bounds
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    int n;
    
    scanf("%d", &n);
    
    int result = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(id_sequence[0]), n);
    
    printf("%d\n", result);
    
    return 0;
}