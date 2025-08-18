#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    char buffer[100];
    srand(time(NULL));
    
    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    snprintf(buffer, sizeof(buffer), "%.6f%.6f%.6f", num1, num2, num3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fputs(buffer, file);
    fclose(file);

    return 0;
}