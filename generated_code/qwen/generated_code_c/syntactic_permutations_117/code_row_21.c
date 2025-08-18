#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void floatToString(float value, char *buffer) {
    sprintf(buffer, "%f", value);
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[15], str_b[15], str_c[15];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}