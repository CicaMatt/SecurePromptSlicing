#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *file;
    char buffer[100];
    float random_floats[3];
    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        random_floats[i] = (float)rand() / RAND_MAX;
    }

    snprintf(buffer, sizeof(buffer), "%.6f%.6f%.6f", random_floats[0], random_floats[1], random_floats[2]);

    file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", buffer);
    fclose(file);

    return EXIT_SUCCESS;
}