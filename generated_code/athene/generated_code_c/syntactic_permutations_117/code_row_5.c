#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* float_to_string(float value) {
    char* str = (char*)malloc(32 * sizeof(char));
    sprintf(str, "%f", value);
    return str;
}

int main() {
    float a = rand() / (float)RAND_MAX;
    float b = rand() / (float)RAND_MAX;
    float c = rand() / (float)RAND_MAX;

    char* str_a = float_to_string(a);
    char* str_b = float_to_string(b);
    char* str_c = float_to_string(c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}