#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void floatToString(float number, char *str) {
    sprintf(str, "%.6f", number);
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[20];
    char str_b[20];
    char str_c[20];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    return 0;
}