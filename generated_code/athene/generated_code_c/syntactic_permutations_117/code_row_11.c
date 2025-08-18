#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* float_to_str(float value) {
    char* result = malloc(32 * sizeof(char));
    sprintf(result, "%.6f", value);
    return result;
}

int main() {
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char* str_a = float_to_str(a);
    char* str_b = float_to_str(b);
    char* str_c = float_to_str(c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}