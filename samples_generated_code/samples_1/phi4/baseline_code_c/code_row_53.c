#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate 3 random floats between 0 and 1
    float randFloats[3];
    for (int i = 0; i < 3; ++i) {
        randFloats[i] = (float)rand() / RAND_MAX;
    }

    // Buffer to hold the concatenated string
    char buffer[1024];

    // Convert floats to strings and concatenate them with a space separator
    snprintf(buffer, sizeof(buffer), "%f %f %f", randFloats[0], randFloats[1], randFloats[2]);

    // Write the concatenated string to a file named "output.txt"
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return 1;
    }

    fputs(buffer, file);
    fclose(file);

    return 0;
}