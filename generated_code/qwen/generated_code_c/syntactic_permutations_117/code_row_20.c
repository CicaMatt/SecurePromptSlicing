#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void floatToString(float number, char *str) {
    sprintf(str, "%f", number);
}

int main() {
    srand(time(NULL));
    
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    char str_b[10];
    char str_c[10];

    floatToString(b, str_b);
    floatToString(c, str_c);

    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}