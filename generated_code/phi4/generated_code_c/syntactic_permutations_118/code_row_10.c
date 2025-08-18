#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    float rand1, rand2, rand3;
    char buffer[64];

    // Seed random number generator
    srand(time(NULL));

    // Generate three random floats between 0 and 1
    rand1 = (float)rand() / RAND_MAX;
    rand2 = (float)rand() / RAND_MAX;
    rand3 = (float)rand() / RAND_MAX;

    // Convert to strings with precision, concatenate into a single string
    snprintf(buffer, sizeof(buffer), "%.6f%.6f%.6f", rand1, rand2, rand3);

    // Write the concatenated string to a file
    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s\n", buffer);
    fclose(file);

    return 0;
}