#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;

    char str1[50], str2[50], str3[50];
    snprintf(str1, sizeof(str1), "%f", num1);
    snprintf(str2, sizeof(str2), "%f", num2);
    snprintf(str3, sizeof(str3), "%f", num3);

    FILE *file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s\n%s\n%s\n", str1, str2, str3);
    fclose(file);

    return 0;
}