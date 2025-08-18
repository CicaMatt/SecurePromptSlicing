#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* floatToString(float num, char* buffer) {
    sprintf(buffer, "%f", num);
    return buffer;
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX * 100.0; // random float between 0 and 100
    float b = (float)rand() / RAND_MAX * 100.0; // random float between 0 and 100
    float c = (float)rand() / RAND_MAX * 100.0; // random float between 0 and 100

    char str_a[50];
    char str_b[50];
    char str_c[50];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}