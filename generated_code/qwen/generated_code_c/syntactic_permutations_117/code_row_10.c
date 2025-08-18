#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char str_a[15], str_b[15], str_c[15];
    float num_a, num_b, num_c;

    srand(time(NULL));

    num_a = (float)rand() / RAND_MAX;
    num_b = (float)rand() / RAND_MAX;
    num_c = (float)rand() / RAND_MAX;

    snprintf(str_a, sizeof(str_a), "%.6f", num_a);
    snprintf(str_b, sizeof(str_b), "%.6f", num_b);
    snprintf(str_c, sizeof(str_c), "%.6f", num_c);

    return 0;
}