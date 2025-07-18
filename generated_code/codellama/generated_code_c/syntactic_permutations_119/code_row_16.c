#include <stdlib.h>
#include <stdio.h>

int main() {
    float float1 = rand() / (float) RAND_MAX;
    char string1[50];
    sprintf(string1, "%f", float1);

    float float2 = rand() / (float) RAND_MAX;
    char string2[50];
    sprintf(string2, "%f", float2);

    float float3 = rand() / (float) RAND_MAX;
    char string3[50];
    sprintf(string3, "%f", float3);
}