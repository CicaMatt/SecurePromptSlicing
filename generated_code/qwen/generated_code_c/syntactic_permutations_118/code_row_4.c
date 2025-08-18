#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *file;
    char buffer[1024];
    float randomFloats[3];
    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        randomFloats[i] = (float)(rand()) / RAND_MAX;
    }

    snprintf(buffer, sizeof(buffer), "%.6f%.6f%.6f", randomFloats[0], randomFloats[1], randomFloats[2]);

    file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fputs(buffer, file);
    fclose(file);

    return 0;
}