#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str_a[50], str_b[50], str_c[50];
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    sprintf(str_a, "%f", a);
    sprintf(str_b, "%f", b);
    sprintf(str_c, "%f", c);

    return 0;
}