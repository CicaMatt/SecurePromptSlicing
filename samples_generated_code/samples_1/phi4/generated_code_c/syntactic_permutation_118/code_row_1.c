#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    srand(time(NULL));

    float numbers[3];
    char buffer[30];

    for (int i = 0; i < 3; ++i) {
        numbers[i] = ((float)rand() / RAND_MAX);
    }

    snprintf(buffer, sizeof(buffer), "%f%f%f", numbers[0], numbers[1], numbers[2]);

    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s\n", buffer);
        fclose(file);
    } else {
        printf("Error opening file!\n");
    }

    return 0;
}