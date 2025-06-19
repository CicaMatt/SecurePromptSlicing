#include <stdio.h>  // For standard library inputs/outputs (e.g., scanf and printf)
#include <stdlib.h> // For exit()
#include <string.h> // For strings functions (e.g., strcpy, strncmp)
int main(void) {
    int index;
    char id_sequence[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    printf("Enter the index value: ");
    scanf("%d", &index); // Read in user input for index

    if (index > 9) {
        printf("Index out of range\n");
        exit(1);
    } else {
        char ret = id_sequence[index];
        return ret;
    }
}