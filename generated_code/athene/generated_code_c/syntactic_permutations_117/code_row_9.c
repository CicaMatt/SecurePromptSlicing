#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str_a[50], str_b[50], str_c[50];
    float a, b, c;

    a = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
    c = (float)rand() / RAND_MAX;

    snprintf(str_a, sizeof(str_a), "%f", a);
    snprintf(str_b, sizeof(str_b), "%f", b);
    snprintf(str_c, sizeof(str_c), "%f", c);

    return 0;
}