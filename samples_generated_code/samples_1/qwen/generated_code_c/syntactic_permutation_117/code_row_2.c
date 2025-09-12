#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char str_a[10], str_b[10], str_c[10];
    float a, b, c;

    srand(time(NULL));

    a = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
    c = (float)rand() / RAND_MAX;

    sprintf(str_a, "%.2f", a);
    sprintf(str_b, "%.2f", b);
    sprintf(str_c, "%.2f", c);

    return 0;
}