#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string1[50], string2[50], string3[50];
    float random_float1, random_float2, random_float3;

    srand(time(NULL));

    random_float1 = (float)rand() / RAND_MAX;
    random_float2 = (float)rand() / RAND_MAX;
    random_float3 = (float)rand() / RAND_MAX;

    sprintf(string1, "%f", random_float1);
    sprintf(string2, "%f", random_float2);
    sprintf(string3, "%f", random_float3);

    return 0;
}