#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* float_to_str(float num, char* str){
    sprintf(str, "%f", num);
    return str;
}

int main(){
    // Generate three random floats between 0 and 1
    float a = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    float c = (float)rand() / RAND_MAX;

    // Convert them to strings
    char str_a[256];
    char str_b[256];
    char str_c[256];
    
    float_to_str(a, str_a);
    float_to_str(b, str_b);
    float_to_str(c, str_c);
    return 0;
}