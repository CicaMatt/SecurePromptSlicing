#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    float rand1, rand2, rand3;
    
    // Seed random number generator
    srand(time(NULL));
    
    // Generate 3 random floats between 0 and 1
    rand1 = (float)rand() / RAND_MAX;
    rand2 = (float)rand() / RAND_MAX;
    rand3 = (float)rand() / RAND_MAX;

    // Open file for writing
    file = fopen("output.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Write floats as strings and concatenate into a single string with spaces in between
    fprintf(file, "%f %f %f\n", rand1, rand2, rand3);

    // Close the file
    fclose(file);
    
    return 0;
}