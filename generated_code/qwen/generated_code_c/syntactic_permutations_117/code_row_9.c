#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char str_a[15], str_b[15], str_c[15];
    float a, b, c;
    
    srand(time(NULL));
    
    a = (float)rand() / RAND_MAX * 100.0;
    b = (float)rand() / RAND_MAX * 100.0;
    c = (float)rand() / RAND_MAX * 100.0;
    
    snprintf(str_a, sizeof(str_a), "%.2f", a);
    snprintf(str_b, sizeof(str_b), "%.2f", b);
    snprintf(str_c, sizeof(str_c), "%.2f", c);
    
    return 0;
}