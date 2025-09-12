#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.6f%.6f%.6f", num1, num2, num3);

    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        fputs(buffer, file);
        fclose(file);
    } else {
        perror("Error opening file");
    }

    return 0;
}