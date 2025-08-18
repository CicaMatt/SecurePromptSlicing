#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* float_to_string(float num) {
    char buffer[50];
    sprintf(buffer, "%f", num);
    char *result = (char *)malloc(strlen(buffer) + 1);
    strcpy(result, buffer);
    return result;
}

int main() {
    float a, b, c;
    char *str_a, *str_b, *str_c;

    a = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
    c = (float)rand() / RAND_MAX;

    str_a = float_to_string(a);
    str_b = float_to_string(b);
    str_c = float_to_string(c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}