#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void floatToString(float value, char *str) {
    sprintf(str, "%f", value);
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[50], str_b[50], str_c[50];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    return 0;
}