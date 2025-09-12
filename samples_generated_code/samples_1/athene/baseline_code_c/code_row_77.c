#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* floatToString(float num) {
    char buffer[50];
    sprintf(buffer, "%f", num);
    char *str = malloc(strlen(buffer) + 1);
    strcpy(str, buffer);
    return str;
}

int main() {
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char *str_a = floatToString(a);
    char *str_b = floatToString(b);
    char *str_c = floatToString(c);

    free(str_a);
    free(str_b);
    free(str_c);

    return 0;
}