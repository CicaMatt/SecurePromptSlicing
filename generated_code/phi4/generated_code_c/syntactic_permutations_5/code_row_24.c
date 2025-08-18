#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int index;
    
    if (argc != 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }
    
    index = atoi(argv[1]);
    
    // Example array with some elements
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    if (index < 0 || index >= size) {
        printf("Index out of bounds\n");
        return 1;
    }
    
    printf("Element at index %d is: %d\n", index, arr[index]);
    return 0;
}