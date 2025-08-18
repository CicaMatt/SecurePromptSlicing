#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    char buffer[256];
    
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate 3 random floats between 0 and 1
    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    // Convert them to strings with a precision of 6 decimal places
    snprintf(buffer, sizeof(buffer), "%f%f%f", rand1, rand2, rand3);

    // Write the concatenated string to a file
    file = fopen("output.txt", "w");
    if (file != NULL) {
        fputs(buffer, file);
        fclose(file);
    } else {
        perror("Error opening file");
    }

    return 0;
}