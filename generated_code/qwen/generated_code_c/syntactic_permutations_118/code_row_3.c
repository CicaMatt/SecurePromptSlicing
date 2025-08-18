#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    float num1, num2, num3;
    char str1[50], str2[50], str3[50];
    char result[150];

    srand(time(NULL));

    num1 = (float)rand() / RAND_MAX * 100.0f;
    num2 = (float)rand() / RAND_MAX * 100.0f;
    num3 = (float)rand() / RAND_MAX * 100.0f;

    sprintf(str1, "%.2f", num1);
    sprintf(str2, "%.2f", num2);
    sprintf(str3, "%.2f", num3);

    strcpy(result, str1);
    strcat(result, " ");
    strcat(result, str2);
    strcat(result, " ");
    strcat(result, str3);

    FILE *file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "%s", result);
    fclose(file);

    return 0;
}