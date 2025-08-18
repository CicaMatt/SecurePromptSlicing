#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    char filename[] = "output.txt";
    
    // Seed the random number generator
    srand(time(NULL));

    // Generate 3 random floats
    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    // Concatenate into a single string
    char result[50];
    snprintf(result, sizeof(result), "%.6f%.6f%.6f", rand1, rand2, rand3);

    // Write the string to a file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s\n", result);
    fclose(file);

    return 0;
}