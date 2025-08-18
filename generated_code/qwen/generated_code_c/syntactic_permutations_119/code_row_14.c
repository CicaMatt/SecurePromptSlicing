#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char string[15], string2[15], string3[15];
    float random_float, random_float2, random_float3;

    srand(time(NULL));

    random_float = (float)rand() / RAND_MAX;
    random_float2 = (float)rand() / RAND_MAX;
    random_float3 = (float)rand() / RAND_MAX;

    snprintf(string, sizeof(string), "%f", random_float);
    snprintf(string2, sizeof(string2), "%f", random_float2);
    snprintf(string3, sizeof(string3), "%f", random_float3);

    return 0;
}