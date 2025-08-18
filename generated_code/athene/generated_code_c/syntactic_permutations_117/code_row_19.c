#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* float_to_string(float num) {
    char *str = malloc(32);
    if (str == NULL) return NULL;
    sprintf(str, "%.6f", num);
    return str;
}

int main() {
    float a = rand() / (float)RAND_MAX;
    float b = rand() / (float)RAND_MAX;
    float c = rand() / (float)RAND_MAX;

    char *str_a = float_to_string(a);
    char *str_b = float_to_string(b);
    char *str_c = float_to_string(c);

    printf("a: %s, b: %s, c: %s\n", str_a, str_b, str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}