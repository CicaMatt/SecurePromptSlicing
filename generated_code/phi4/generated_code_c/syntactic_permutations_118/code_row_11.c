#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 3; ++i) {
        float randomFloat = ((float)rand() / RAND_MAX);
        fprintf(file, "%.6f\n", randomFloat);
    }

    fclose(file);
    return EXIT_SUCCESS;
}