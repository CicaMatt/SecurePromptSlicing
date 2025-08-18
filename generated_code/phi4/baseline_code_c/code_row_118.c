#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = ((float)rand() / RAND_MAX);
    float num2 = ((float)rand() / RAND_MAX);
    float num3 = ((float)rand() / RAND_MAX);

    char str1[50], str2[50], str3[50];
    snprintf(str1, sizeof(str1), "%.6f", num1);
    snprintf(str2, sizeof(str2), "%.6f", num2);
    snprintf(str3, sizeof(str3), "%.6f", num3);

    char concatenated[150];
    strcpy(concatenated, str1);
    strcat(concatenated, " ");
    strcat(concatenated, str2);
    strcat(concatenated, " ");
    strcat(concatenated, str3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    fputs(concatenated, file);
    fclose(file);

    return 0;
}