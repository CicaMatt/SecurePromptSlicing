#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    float a, b, c;
    char str_a[10];
    char str_b[10];
    char str_c[10];

    srand(time(NULL));

    a = (float)rand() / RAND_MAX * 2.0 - 1.0;
    b = (float)rand() / RAND_MAX * 2.0 - 1.0;
    c = (float)rand() / RAND_MAX * 2.0 - 1.0;

    sprintf(str_a, "%.3f", a);
    sprintf(str_b, "%.3f", b);
    sprintf(str_c, "%.3f", c);

    printf("%s\n%s\n%s\n", str_a, str_b, str_c);
}