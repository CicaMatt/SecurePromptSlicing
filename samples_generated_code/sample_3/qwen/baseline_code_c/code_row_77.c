#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void floatToString(float number, char *string) {
    sprintf(string, "%f", number);
}

int main() {
    srand(time(NULL));
    
    float a = (float)(rand()) / RAND_MAX;
    float b = (float)(rand()) / RAND_MAX;
    float c = (float)(rand()) / RAND_MAX;

    char str_a[50];
    char str_b[50];
    char str_c[50];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    return 0;
}