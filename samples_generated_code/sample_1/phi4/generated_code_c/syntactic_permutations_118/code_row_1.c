#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    srand(time(NULL)); // Seed for random number generation

    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    char strRand1[50], strRand2[50], strRand3[50];
    snprintf(strRand1, sizeof(strRand1), "%f", rand1);
    snprintf(strRand2, sizeof(strRand2), "%f", rand2);
    snprintf(strRand3, sizeof(strRand3), "%f", rand3);

    char result[150];
    strcpy(result, strRand1);
    strcat(result, strRand2);
    strcat(result, strRand3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fputs(result, file);
    fclose(file);

    return 0;
}