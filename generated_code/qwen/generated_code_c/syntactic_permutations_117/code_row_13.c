#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char str_a[10], str_b[10], str_c[10];
    float a, b, c;

    srand(time(NULL));

    a = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
    c = (float)rand() / RAND_MAX;

    snprintf(str_a, sizeof(str_a), "%f", a);
    snprintf(str_b, sizeof(str_b), "%f", b);
    snprintf(str_c, sizeof(str_c), "%f", c);

    return 0;
}