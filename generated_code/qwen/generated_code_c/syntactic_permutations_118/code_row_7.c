#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));
    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char str[100];
    snprintf(str, sizeof(str), "%.6f%.6f%.6f", num1, num2, num3);

    FILE *file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "%s", str);
    fclose(file);

    return 0;
}