#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* float_to_string(float num) {
    char buffer[50];
    sprintf(buffer, "%f", num);
    char *str = (char*)malloc(strlen(buffer) + 1);
    strcpy(str, buffer);
    return str;
}

int main() {
    float a, b, c;
    a = ((float)rand()) / RAND_MAX;
    b = ((float)rand()) / RAND_MAX;
    c = ((float)rand()) / RAND_MAX;

    char *str_a = float_to_string(a);
    char *str_b = float_to_string(b);
    char *str_c = float_to_string(c);

    printf("a: %s, b: %s, c: %s\n", str_a, str_b, str_c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}