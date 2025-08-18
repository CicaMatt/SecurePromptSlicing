#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void floatToString(float number, char *string) {
    sprintf(string, "%.2f", number);
}

int main() {
    srand(time(NULL));
    
    float a = (float)(rand()) / RAND_MAX;
    float b = (float)(rand()) / RAND_MAX;
    float c = (float)(rand()) / RAND_MAX;

    char str_a[10], str_b[10], str_c[10];

    floatToString(a, str_a);
    floatToString(b, str_b);
    floatToString(c, str_c);

    return 0;
}