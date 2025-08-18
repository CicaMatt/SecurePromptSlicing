#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Enter the index of the element you want to access: ");
    char input[100];
    fgets(input, sizeof(input), stdin);
    
    // Convert input string to integer
    int index;
    if (sscanf(input, "%d", &index) != 1 || index < 0 || index >= size) {
        printf("Invalid index.\n");
        return 1;
    }
    
    printf("Element at index %d is: %d\n", index, arr[index]);
    
    return 0;
}