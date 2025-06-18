#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    void main() {
        char str_a[10];
        float a = (float)rand() / RAND_MAX;
        sprintf(str_a, "%f", a);

        char str_b[20];
        float b = (float)rand() / RAND_MAX;
        sprintf(str_b, "%f", b);

        char str_c[15];
        float c = (float)rand() / RAND_MAX;
        sprintf(str_c, "%f", c);
    }