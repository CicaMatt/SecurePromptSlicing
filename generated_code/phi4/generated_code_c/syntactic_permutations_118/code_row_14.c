#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    srand(time(NULL));

    float rand1 = ((float)rand() / RAND_MAX);
    float rand2 = ((float)rand() / RAND_MAX);
    float rand3 = ((float)rand() / RAND_MAX);

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%f.%f%f", rand1 * 1000000, (int)(rand2 * 1000000) % 10, (int)(rand3 * 10000000) % 100);
    
    fprintf(file, "Concatenated: %s\n", buffer);

    fclose(file);
    return EXIT_SUCCESS;
}