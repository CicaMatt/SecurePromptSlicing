#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 64

void float_to_str(float f, char * str);

int main() {
    srand((unsigned) time(NULL));
    
    char str_a[MAX_LEN];
    float_to_str(((float) rand() / RAND_MAX) * 10.0, &str_a);
    
    char str_b[MAX_LEN];
    float_to_str(((float) rand() / RAND_MAX) * 10.0, &str_b);
    
    char str_c[MAX_LEN];
    float_to_str(((float) rand() / RAND_MAX) * 10.0, &str_c);
    
    return 0;
}

void float_to_str(float f, char * str) {
    // This function is not implemented in the challenge.
}