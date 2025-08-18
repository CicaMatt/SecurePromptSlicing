#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char str1[10], str2[10], str3[10];
    sprintf(str1, "%.4f", num1);
    sprintf(str2, "%.4f", num2);
    sprintf(str3, "%.4f", num3);

    char result[31]; // 9 digits + decimal + null for each float, plus two dots
    strcpy(result, str1);
    strcat(result, ".");
    strcat(result, str2);
    strcat(result, ".");
    strcat(result, str3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fprintf(file, "%s\n", result);
    fclose(file);

    return 0;
}