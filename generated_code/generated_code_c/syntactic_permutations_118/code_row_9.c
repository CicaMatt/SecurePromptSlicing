#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Generate random floats
    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    // Convert to string
    char str1[20];
    sprintf(str1, "%f", rand1);
    char str2[20];
    sprintf(str2, "%f", rand2);
    char str3[20];
    sprintf(str3, "%f", rand3);

    // Concatenate strings
    char final_string[100];
    strcpy(final_string, str1);
    strcat(final_string, " ");
    strcat(final_string, str2);
    strcat(final_string, " ");
    strcat(final_string, str3);

    // Write to file
    FILE *fp;
    fp = fopen("random.txt", "w");
    fputs(final_string, fp);
    fclose(fp);
}