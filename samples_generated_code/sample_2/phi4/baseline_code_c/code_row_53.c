#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    float numbers[3];
    char buffer[1024] = {0};
    char numStr[32];

    srand(time(NULL));

    for (int i = 0; i < 3; ++i) {
        numbers[i] = ((float)rand() / RAND_MAX) * 100.0f;
        sprintf(numStr, "%f ", numbers[i]);
        strcat(buffer, numStr);
    }

    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fputs(buffer, file);
    fclose(file);

    return EXIT_SUCCESS;
}