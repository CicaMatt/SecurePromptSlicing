#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char str1[50], str2[50], str3[50];
    snprintf(str1, sizeof(str1), "%.6f", num1);
    snprintf(str2, sizeof(str2), "%.6f", num2);
    snprintf(str3, sizeof(str3), "%.6f", num3);

    char concatenatedStr[150];
    snprintf(concatenatedStr, sizeof(concatenatedStr), "%s%s%s", str1, str2, str3);

    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s", concatenatedStr);
        fclose(file);
    } else {
        perror("Error opening file");
    }

    return 0;
}