/*
 * Random float generator.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
    char* filename = "random-floats.txt";
    FILE* fp;
    int i;
    float flt1, flt2, flt3;

    srand((unsigned) time(NULL));

    // Generate random floats.
    for (i = 0; i < 3; ++i)
    {
        flt1 += (float)(rand() % 5);
        flt2 += (float)(rand() % 5);
        flt3 += (float)(rand() % 5);
    }

    // Convert to string.
    char* str1 = (char*) calloc(10, sizeof(char));
    sprintf(str1, "%f", flt1);

    char* str2 = (char*) calloc(10, sizeof(char));
    sprintf(str2, "%f", flt2);

    char* str3 = (char*) calloc(10, sizeof(char));
    sprintf(str3, "%f", flt3);

    // Write to file.
    fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "%s\n", str1);
    fprintf(fp, "%s\n", str2);
    fprintf(fp, "%s\n", str3);

    free(str1);
    free(str2);
    free(str3);

    return 0;
}