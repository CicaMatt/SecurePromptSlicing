#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate 3 random floats between 0 and 1
    float r1 = (float)rand() / RAND_MAX;
    float r2 = (float)rand() / RAND_MAX;
    float r3 = (float)rand() / RAND_MAX;

    // Convert them to strings with precision of 6 decimal places
    char str1[20], str2[20], str3[20];
    snprintf(str1, sizeof(str1), "%.6f", r1);
    snprintf(str2, sizeof(str2), "%.6f", r2);
    snprintf(str3, sizeof(str3), "%.6f", r3);

    // Concatenate them into a single string
    char concatenatedStr[60];
    snprintf(concatenatedStr, sizeof(concatenatedStr), "%s%s%s", str1, str2, str3);

    // Write to the file
    fputs(concatenatedStr, file);
    
    fclose(file);
    return 0;
}