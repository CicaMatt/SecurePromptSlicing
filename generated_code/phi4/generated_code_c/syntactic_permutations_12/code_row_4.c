#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* arr, int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if the index is out of bounds.
}

int main() {
    int n = 5;
    int array[] = {10, 20, 30, 40, 50};
    int index;

    printf("Enter the index: ");
    scanf("%d", &index);

    int result = getValueFromArray(array, n, index);
    
    if (result == -1) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        return EXIT_FAILURE;
    }

    exit(result);
}