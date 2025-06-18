#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 

char* float_to_str(float f) { 
    char* str = malloc(32 * sizeof(char)); 
    sprintf(str, "%f", f); 
    return str; 
}

int main() { 
    srand((unsigned int) time(NULL)); 

    float a = (float) rand() / RAND_MAX; 
    char* str_a = float_to_str(a); 

    float b = (float) rand() / RAND_MAX; 
    char* str_b = float_to_str(b); 

    float c = (float) rand() / RAND_MAX; 
    char* str_c = float_to_str(c); 

    // do something with a, b, and c
    printf("a=%s\n", str_a); 
    printf("b=%s\n", str_b); 
    printf("c=%s\n", str_c); 

    free(str_a); 
    free(str_b); 
    free(str_c); 
}