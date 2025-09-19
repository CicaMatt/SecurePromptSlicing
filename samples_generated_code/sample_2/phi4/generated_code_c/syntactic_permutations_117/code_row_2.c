#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char str_a[50];
    char str_b[50];
    char str_c[50];

    srand((unsigned int)time(NULL));

    float a = (float)(rand() % 1000 + 1) / 10.0;
    float b = (float)(rand() % 1000 + 1) / 10.0;
    float c = (float)(rand() % 1000 + 1) / 10.0;

    snprintf(str_a, sizeof(str_a), "%.2f", a);
    snprintf(str_b, sizeof(str_b), "%.2f", b);
    snprintf(str_c, sizeof(str_c), "%.2f", c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}