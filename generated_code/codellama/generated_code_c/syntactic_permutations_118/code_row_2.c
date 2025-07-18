#include <stdio.h>
#include <stdlib.h> // For srand() and rand()
#include <time.h>   // For time()
#include <string.h> // For strcat()

int main(void) {
    // Set seed for rand() using the current time.
    srand((unsigned int) time(NULL));

    char file_contents[100];

    // Generate 3 random floats and convert to strings
    float f = (float) rand() / RAND_MAX;
    char str_f[256];
    snprintf(str_f, sizeof(str_f), "%.4f", f);

    float g = (float) rand() / RAND_MAX;
    char str_g[256];
    snprintf(str_g, sizeof(str_g), "%.4f", g);

    float h = (float) rand() / RAND_MAX;
    char str_h[256];
    snprintf(str_h, sizeof(str_h), "%.4f", h);

    // Concatenate the strings into a single string
    strcat(file_contents, str_f);
    strcat(file_contents, " ");
    strcat(file_contents, str_g);
    strcat(file_contents, " ");
    strcat(file_contents, str_h);

    // Writes the string to a file
    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "%s\n", file_contents);

    return 0;
}