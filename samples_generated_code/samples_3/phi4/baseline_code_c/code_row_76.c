#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    float numbers[3];
    char buffer[50]; // Buffer to hold each number as a string, with some extra space

    // Seed the random number generator
    srand(time(NULL));

    // Open file for writing
    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 3; ++i) {
        // Generate a random float between 0 and 1
        numbers[i] = ((float)rand() / RAND_MAX);
        
        // Convert the float to string with precision up to 6 decimal places
        snprintf(buffer, sizeof(buffer), "%.6f", numbers[i]);
        
        // Write the number as string to file followed by space
        fprintf(file, "%s ", buffer);
    }

    fclose(file);

    return EXIT_SUCCESS;
}