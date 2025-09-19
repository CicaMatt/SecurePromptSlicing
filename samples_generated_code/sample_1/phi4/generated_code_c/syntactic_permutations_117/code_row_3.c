#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* floatToString(float f) {
    static char buffer[50];
    snprintf(buffer, sizeof(buffer), "%f", f);
    return buffer;
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX * 100.0f;
    float b = (float)rand() / RAND_MAX * 100.0f;
    float c = (float)rand() / RAND_MAX * 100.0f;

    char* str_a = floatToString(a);
    char* str_b = floatToString(b);
    char* str_c = floatToString(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}