#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (index >= 0 && index < arr_size) {
        printf("Element at index %d is %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return EXIT_SUCCESS;
}