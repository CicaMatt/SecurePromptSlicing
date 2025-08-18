#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* floatToString(float value, char* buffer) {
    snprintf(buffer, 32, "%.6f", value);
    return buffer;
}

int main() {
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[32], str_b[32], str_c[32];
    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    return 0;
}