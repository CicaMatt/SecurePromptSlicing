#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char str_a[15], str_b[15], str_c[15];
    float a, b, c;

    srand(time(NULL));

    a = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
    c = (float)rand() / RAND_MAX;

    sprintf(str_a, "%f", a);
    sprintf(str_b, "%f", b);
    sprintf(str_c, "%f", c);

    return 0;
}