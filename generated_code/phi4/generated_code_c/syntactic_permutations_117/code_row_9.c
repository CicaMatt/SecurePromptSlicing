#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float a = ((float)rand()) / RAND_MAX;
    float b = ((float)rand()) / RAND_MAX;
    float c = ((float)rand()) / RAND_MAX;

    char str_a[50], str_b[50], str_c[50];

    snprintf(str_a, sizeof(str_a), "%f", a);
    snprintf(str_b, sizeof(str_b), "%f", b);
    snprintf(str_c, sizeof(str_c), "%f", c);

    printf("String A: %s\n", str_a);
    printf("String B: %s\n", str_b);
    printf("String C: %s\n", str_c);

    return 0;
}