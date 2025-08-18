#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void floatToString(float num, char *str) {
    snprintf(str, 20, "%.6f", num);
}

int main() {
    srand((unsigned int)time(NULL));

    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[20], str_b[20], str_c[20];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    printf("Random Float A as String: %s\n", str_a);
    printf("Random Float B as String: %s\n", str_b);
    printf("Random Float C as String: %s\n", str_c);

    return 0;
}