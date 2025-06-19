#include <stdio.h>
#include <stdlib.h>
 
int main() {
    // Allocate memory for first chunk
    int* first_chunk = malloc(5 * sizeof(int));
 
    // Initialize the first chunk to contain 1,2,3,4,5
    for (int i = 0; i < 5; i++) {
        first_chunk[i] = i + 1;
    }
 
    // Allocate memory for second chunk
    int* second_chunk = malloc(7 * sizeof(int));
 
    // Copy the contents of the first chunk into the second chunk
    for (int i = 0; i < 5; i++) {
        second_chunk[i] = first_chunk[i];
    }
 
    // Print the contents of the second chunk
    printf("Second Chunk: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", second_chunk[i]);
    }
    printf("\n");
 
    // Free memory allocated to first chunk
    free(first_chunk);
 
    // Print the contents of the second chunk again
    printf("Second Chunk: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", second_chunk[i]);
    }
    printf("\n");
 
    // Free memory allocated to second chunk
    free(second_chunk);
 
    return 0;
}