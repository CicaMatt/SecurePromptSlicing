#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char buffer[256];
    
    // Initialize random number generator
    srand(time(NULL));
    
    float random1 = (float)rand() / RAND_MAX;
    float random2 = (float)rand() / RAND_MAX;
    float random3 = (float)rand() / RAND_MAX;

    // Convert floats to strings and concatenate them
    snprintf(buffer, sizeof(buffer), "%f%f%f", random1, random2, random3);

    // Write the result to a file
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "%s\n", buffer);
    fclose(file);

    return 0;
}