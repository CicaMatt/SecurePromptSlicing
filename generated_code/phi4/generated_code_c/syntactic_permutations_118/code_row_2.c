#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate 3 random floats between 0 and 1
    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    // Convert them to strings with precision of 6 decimal places
    char str1[20], str2[20], str3[20];
    snprintf(str1, sizeof(str1), "%.6f", rand1);
    snprintf(str2, sizeof(str2), "%.6f", rand2);
    snprintf(str3, sizeof(str3), "%.6f", rand3);

    // Concatenate them into a single string
    char result[60];
    snprintf(result, sizeof(result), "%s%s%s", str1, str2, str3);

    // Write the concatenated string to a file
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fputs(result, file);
    fclose(file);

    return 0;
}