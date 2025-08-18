#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%f%f%f", rand1, rand2, rand3);

    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s\n", buffer);
        fclose(file);
    } else {
        perror("Error opening file");
    }

    return 0;
}