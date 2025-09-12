#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void floatToString(float number, char *str) {
    sprintf(str, "%f", number);
}

int main() {
    srand(time(NULL));
    
    float num_a = (float)(rand()) / RAND_MAX;
    float num_b = (float)(rand()) / RAND_MAX;
    float num_c = (float)(rand()) / RAND_MAX;

    char str_a[50], str_b[50], str_c[50];

    floatToString(num_a, str_a);
    floatToString(num_b, str_b);
    floatToString(num_c, str_c);

    return 0;
}