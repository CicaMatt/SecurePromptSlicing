#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* floatToString(float f) {
    static char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.6f", f);
    return buffer;
}

int main() {
    srand(time(NULL));

    float rand_a = (float)rand() / RAND_MAX * 100.0;
    float rand_b = (float)rand() / RAND_MAX * 100.0;
    float rand_c = (float)rand() / RAND_MAX * 100.0;

    char* str_a = floatToString(rand_a);
    char* str_b = floatToString(rand_b);
    char* str_c = floatToString(rand_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}