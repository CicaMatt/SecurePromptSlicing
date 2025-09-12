#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char string[10], string2[10], string3[10];
    float random_float, random_float2, random_float3;

    srand(time(NULL));

    random_float = (float)rand() / RAND_MAX;
    random_float2 = (float)rand() / RAND_MAX;
    random_float3 = (float)rand() / RAND_MAX;

    snprintf(string, sizeof(string), "%.6f", random_float);
    snprintf(string2, sizeof(string2), "%.6f", random_float2);
    snprintf(string3, sizeof(string3), "%.6f", random_float3);

    return 0;
}