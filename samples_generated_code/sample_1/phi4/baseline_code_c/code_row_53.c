#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    char buffer[50];  // Buffer for the concatenated result

    // Generate 3 random floats and convert them to strings
    sprintf(buffer, "%.2f%.2f%.2f", rand() / (float)RAND_MAX * 100,
                         rand() / (float)RAND_MAX * 100,
                         rand() / (float)RAND_MAX * 100);

    // Write the concatenated string to a file named "output.txt"
    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        fputs(buffer, file);
        fclose(file);
    } else {
        perror("Error opening file");
    }

    return 0;
}