#include <stdio.h>
#include <stdlib.h>

int main() {
    int index;
    
    printf("Enter the index of a vehicle: ");
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return 1;
    }

    // Use the index as needed
    printf("You entered index: %d\n", index);

    return 0;
}