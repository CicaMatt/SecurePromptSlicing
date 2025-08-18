#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Seed the random number generator
    srand((unsigned int) time(NULL));

    char buffer[50];
    for (int i = 0; i < 3; ++i) {
        float randFloat = ((float)rand() / RAND_MAX);
        snprintf(buffer, sizeof(buffer), "%f", randFloat);

        // Append a space between numbers
        if (i > 0) {
            strcat(buffer, " ");
        }

        fputs(buffer, file);
    }
    
    fclose(file);
    return 0;
}