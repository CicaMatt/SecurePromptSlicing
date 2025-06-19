#include <stdio.h>
#include <stdlib.h>
int main(void) {
    // Generating 3 random floats.
    float f1 = (float)(rand() % 100);
    float f2 = (float)(rand() % 100);
    float f3 = (float)(rand() % 100);

    // Converting to strings.
    char str_f1[256];
    sprintf(str_f1, "%.2f", f1);

    char str_f2[256];
    sprintf(str_f2, "%.2f", f2);

    char str_f3[256];
    sprintf(str_f3, "%.2f", f3);

    // Concatenating into a single string.
    char str_all[256];
    sprintf(str_all, "Random floats: %s, %s, %s", str_f1, str_f2, str_f3);

    // Write the string to file.
    FILE *fp;
    fp = fopen("random.txt", "a+");
    if (fp == NULL)
        return 0;

    fputs(str_all, fp);
    fclose(fp);
    return 1;
}