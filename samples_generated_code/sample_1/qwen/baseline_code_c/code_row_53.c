#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    float num1, num2, num3;
    char strNum1[20], strNum2[20], strNum3[20];
    char result[60];

    srand(time(NULL));

    num1 = (float)rand() / RAND_MAX * 100.0;
    num2 = (float)rand() / RAND_MAX * 100.0;
    num3 = (float)rand() / RAND_MAX * 100.0;

    sprintf(strNum1, "%.2f", num1);
    sprintf(strNum2, "%.2f", num2);
    sprintf(strNum3, "%.2f", num3);

    strcpy(result, strNum1);
    strcat(result, strNum2);
    strcat(result, strNum3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s", result);
    fclose(file);

    return 0;
}