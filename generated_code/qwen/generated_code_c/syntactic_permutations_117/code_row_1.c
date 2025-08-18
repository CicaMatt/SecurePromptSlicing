#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void float_to_string(float number, char *str) {
    sprintf(str, "%.2f", number);
}

int main() {
    srand(time(NULL));
    
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[10], str_b[10], str_c[10];

    float_to_string(a, str_a);
    float_to_string(b, str_b);
    float_to_string(c, str_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}