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
    snprintf(str1, sizeof(str1), "%.4f", num1);
    snprintf(str2, sizeof(str2), "%.4f", num2);
    snprintf(str3, sizeof(str3), "%.4f", num3);
    
    char result[150];
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);
    
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }
    
    fprintf(file, "%s", result);
    fclose(file);
    
    return 0;
}