#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int index = 2; // Example index to convert and use
    char indexStr[] = "2"; // String representation of the index

    // Convert string to integer
    index = atoi(indexStr);

    // Check if index is within bounds
    if (index >= 0 && index < sizeof(array) / sizeof(array[0])) {
        printf("Element at index %d is %d\n", index, array[index]);
    } else {
        printf("Index out of bounds\n");
    }

    return 0;
}