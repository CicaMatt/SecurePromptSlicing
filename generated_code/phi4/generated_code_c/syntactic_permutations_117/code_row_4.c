#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void floatToString(float number, char *str) {
    sprintf(str, "%f", number);
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[20], str_b[20], str_c[20];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    printf("String a: %s\n", str_a);
    printf("String b: %s\n", str_b);
    printf("String c: %s\n", str_c);

    return 0;
}