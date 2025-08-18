#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* float_to_string(float value) {
    static char buffer[50];
    snprintf(buffer, sizeof(buffer), "%f", value);
    return buffer;
}

int main() {
    srand(time(NULL));

    float a = (float)rand() / RAND_MAX * 100.0; // Generate random float between 0 and 100
    float b = (float)rand() / RAND_MAX * 100.0;
    float c = (float)rand() / RAND_MAX * 100.0;

    char* str_a = float_to_string(a);
    char* str_b = float_to_string(b);
    char* str_c = float_to_string(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}