#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double generateRandomFloat() {
    return (double)rand() / RAND_MAX;
}

void floatToString(double num, char *str, int precision) {
    sprintf(str, "%.*f", precision, num);
}

int main() {
    srand(time(NULL));

    double a = generateRandomFloat();
    double b = generateRandomFloat();
    double c = generateRandomFloat();

    char str_a[50], str_b[50], str_c[50];

    floatToString(a, str_a, 6);
    floatToString(b, str_b, 6);
    floatToString(c, str_c, 6);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}