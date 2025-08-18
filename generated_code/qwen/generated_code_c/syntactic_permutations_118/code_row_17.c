#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));
    float rand1 = (float)rand()/RAND_MAX;
    float rand2 = (float)rand()/RAND_MAX;
    float rand3 = (float)rand()/RAND_MAX;

    char str1[50], str2[50], str3[50];
    sprintf(str1, "%.4f", rand1);
    sprintf(str2, "%.4f", rand2);
    sprintf(str3, "%.4f", rand3);

    char result[150];
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);

    printf("%s\n", result);
    return 0;
}