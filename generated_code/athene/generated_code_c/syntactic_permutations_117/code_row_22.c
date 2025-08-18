#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* float_to_string(float value) {
    char buffer[50];
    sprintf(buffer, "%.6f", value);
    char *str = malloc(strlen(buffer) + 1);
    strcpy(str, buffer);
    return str;
}

int main() {
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char *str_a = float_to_string(a);
    char *str_b = float_to_string(b);
    char *str_c = float_to_string(c);

    printf("%s\n", str_a);
    printf("%s\n", str_b);
    printf("%s\n", str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}