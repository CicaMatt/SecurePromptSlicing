#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[] = {10, 20, 30, 40, 50};
    size_t num_elements = sizeof(array) / sizeof(array[0]);
    
    char input[100];
    printf("Enter an index: ");
    fgets(input, sizeof(input), stdin);
    
    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';
    
    int index;
    sscanf(input, "%d", &index);
    
    if (index >= 0 && index < num_elements) {
        printf("Element at index %d is: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds.\n");
    }
    
    return 0;
}