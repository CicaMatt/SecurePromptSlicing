#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char str1[50], str2[50], str3[50];
    sprintf(str1, "%f", num1);
    sprintf(str2, "%f", num2);
    sprintf(str3, "%f", num3);

    char result[150];
    snprintf(result, sizeof(result), "%s%s%s", str1, str2, str3);

    printf("%s\n", result);

    return 0;
}