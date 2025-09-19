#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    float num1, num2, num3;
    char str1[50], str2[50], str3[50];
    char result[150];

    srand(time(NULL));

    num1 = (float)rand() / RAND_MAX;
    num2 = (float)rand() / RAND_MAX;
    num3 = (float)rand() / RAND_MAX;

    sprintf(str1, "%.4f", num1);
    sprintf(str2, "%.4f", num2);
    sprintf(str3, "%.4f", num3);

    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fprintf(file, "%s", result);
    fclose(file);

    return 0;
}