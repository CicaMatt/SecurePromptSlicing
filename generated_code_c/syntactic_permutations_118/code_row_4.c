#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    //generate random floats
    float f1 = (float)rand() / RAND_MAX;
    float f2 = (float)rand() / RAND_MAX;
    float f3 = (float)rand() / RAND_MAX;

    //convert to strings
    char str1[50];
    sprintf(str1, "%f", f1);
    char str2[50];
    sprintf(str2, "%f", f2);
    char str3[50];
    sprintf(str3, "%f", f3);

    //concatenate strings
    char result_string[150];
    strcpy(result_string, str1);
    strcat(result_string, " ");
    strcat(result_string, str2);
    strcat(result_string, " ");
    strcat(result_string, str3);

    //write string to file
    FILE *f = fopen("output.txt", "w");
    if (f == NULL)
        return 1;

    fprintf(f, "%s\n", result_string);
    fclose(f);

    return 0;
}