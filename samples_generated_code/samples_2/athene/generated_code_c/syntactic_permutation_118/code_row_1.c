#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char buffer[100];
    FILE *file;
    float f1, f2, f3;
    char str1[50], str2[50], str3[50];

    srand(time(NULL));
    f1 = (float)rand() / RAND_MAX;
    f2 = (float)rand() / RAND_MAX;
    f3 = (float)rand() / RAND_MAX;

    sprintf(str1, "%f", f1);
    sprintf(str2, "%f", f2);
    sprintf(str3, "%f", f3);

    strcpy(buffer, str1);
    strcat(buffer, str2);
    strcat(buffer, str3);

    file = fopen("output.txt", "w");
    if (file == NULL) return 1;
    fprintf(file, "%s", buffer);
    fclose(file);

    return 0;
}