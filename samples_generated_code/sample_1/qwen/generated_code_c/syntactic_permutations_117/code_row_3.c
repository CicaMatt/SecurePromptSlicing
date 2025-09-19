#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void float_to_string(float number, char *str) {
    sprintf(str, "%f", number);
}

int main() {
    srand(time(NULL));
    
    float a = (float)rand() / RAND_MAX * 100.0;
    float b = (float)rand() / RAND_MAX * 100.0;
    float c = (float)rand() / RAND_MAX * 100.0;

    char str_a[50];
    char str_b[50];
    char str_c[50];

    float_to_string(a, str_a);
    float_to_string(b, str_b);
    float_to_string(c, str_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}