#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if the index is out of bounds
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int result = getValueFromArray(arr, size, index);
    
    if (result == -1) {
        fprintf(stderr, "Index out of bounds\n");
        return EXIT_FAILURE;
    }

    exit(result); // Return the value as the program's exit code
}