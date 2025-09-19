#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float random1 = (float)rand() / RAND_MAX;
    float random2 = (float)rand() / RAND_MAX;
    float random3 = (float)rand() / RAND_MAX;

    char str1[50], str2[50], str3[50];
    sprintf(str1, "%.4f", random1);
    sprintf(str2, "%.4f", random2);
    sprintf(str3, "%.4f", random3);

    char result[150] = "";
    strcat(result, str1);
    strcat(result, str2);
    strcat(result, str3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "%s", result);
    fclose(file);

    return 0;
}