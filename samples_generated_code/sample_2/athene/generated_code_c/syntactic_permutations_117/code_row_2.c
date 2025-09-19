#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[50], str_b[50], str_c[50];
    sprintf(str_a, "%.6f", a);
    sprintf(str_b, "%.6f", b);
    sprintf(str_c, "%.6f", c);

    return 0;
}