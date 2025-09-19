#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char str_a[10], str_b[10], str_c[10];
    float num_a, num_b, num_c;

    srand(time(NULL));

    num_a = (float)rand() / RAND_MAX;
    num_b = (float)rand() / RAND_MAX;
    num_c = (float)rand() / RAND_MAX;

    sprintf(str_a, "%.6f", num_a);
    sprintf(str_b, "%.6f", num_b);
    sprintf(str_c, "%.6f", num_c);

    return 0;
}