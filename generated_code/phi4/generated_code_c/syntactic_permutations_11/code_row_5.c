#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if the index is out of bounds.
}

int main() {
    static const int id_sequence[] = {10, 20, 30, 40, 50};
    int n;
    
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        return -2; // Return an error value for invalid input.
    }

    int result = getValueFromArray(id_sequence, sizeof(id_sequence)/sizeof(id_sequence[0]), n);
    exit(result);
}