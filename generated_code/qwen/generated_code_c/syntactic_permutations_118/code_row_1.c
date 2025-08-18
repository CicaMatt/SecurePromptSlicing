#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char str1[50], str2[50], str3[50];
    sprintf(str1, "%.4f", num1);
    sprintf(str2, "%.4f", num2);
    sprintf(str3, "%.4f", num3);

    char result[150] = "";
    strcat(result, str1);
    strcat(result, str2);
    strcat(result, str3);

    FILE *file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "%s", result);
    fclose(file);

    return 0;
}