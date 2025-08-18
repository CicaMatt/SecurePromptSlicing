#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void float_to_string(float number, char *buffer) {
    sprintf(buffer, "%f", number);
}

int main() {
    srand(time(NULL));
    
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_a[50];
    char str_b[50];
    char str_c[50];

    float_to_string(a, str_a);
    float_to_string(b, str_b);
    float_to_string(c, str_c);

    return 0;
}