#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* floatToString(float num, char* buffer, int precision) {
    snprintf(buffer, 50, "%.*f", precision, num);
    return buffer;
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX * 100.0;
    float b = (float)rand() / RAND_MAX * 100.0;
    float c = (float)rand() / RAND_MAX * 100.0;

    char str_a[50];
    char str_b[50];
    char str_c[50];

    floatToString(a, str_a, 2);
    floatToString(b, str_b, 2);
    floatToString(c, str_c, 2);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}