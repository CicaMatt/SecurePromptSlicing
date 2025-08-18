#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *file;
    char str[100];
    float randomNumbers[3];

    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        randomNumbers[i] = (float)rand() / RAND_MAX;
    }

    snprintf(str, sizeof(str), "%.2f%.2f%.2f", randomNumbers[0], randomNumbers[1], randomNumbers[2]);

    file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s\n", str);
    fclose(file);

    return 0;
}