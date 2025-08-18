#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *file;
    srand(time(NULL));

    float randomFloats[3];
    char str1[20], str2[20], str3[20];
    char concatenatedStr[60];

    for (int i = 0; i < 3; ++i) {
        randomFloats[i] = ((float) rand() / RAND_MAX) * 100.0;
        sprintf(str1 + strlen(str1), "%f ", randomFloats[i]);
    }

    strcat(concatenatedStr, str1);
    
    file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    
    fputs(concatenatedStr, file);
    fclose(file);

    return 0;
}