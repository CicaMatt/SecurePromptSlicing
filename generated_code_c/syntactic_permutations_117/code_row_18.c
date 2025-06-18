// This program generates three random floats and converts them to strings using the 
// atof() function. The resulting strings are stored in str_b and str_c.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *str_a;
    char *str_b;
    char *str_c;
    float num1, num2, num3;
    
    // Generate three random floats and convert them to strings using atof().
    srand(time(NULL));
    num1 = (float) rand() / RAND_MAX;
    str_a = atof(num1);
    num2 = (float) rand() / RAND_MAX;
    str_b = atof(num2);
    num3 = (float) rand() / RAND_MAX;
    str_c = atof(num3);
    
    // Print the strings.
    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);
    
    return 0;
}