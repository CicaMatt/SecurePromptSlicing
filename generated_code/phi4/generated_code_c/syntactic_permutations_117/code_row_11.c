#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double generateRandomFloat() {
    return (double)rand() / RAND_MAX;
}

char* floatToString(double num, char* buffer, int precision) {
    snprintf(buffer, 64, "%.*f", precision, num);
    return buffer;
}

int main() {
    srand(time(NULL));

    double a = generateRandomFloat();
    double b = generateRandomFloat();
    double c = generateRandomFloat();

    char str_a[64];
    char str_b[64];
    char str_c[64];

    floatToString(a, str_a, 3);
    floatToString(b, str_b, 3);
    floatToString(c, str_c, 3);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}