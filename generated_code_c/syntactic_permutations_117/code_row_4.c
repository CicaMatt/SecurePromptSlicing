#include <stdio.h>
#include<stdlib.h>
int main() {
    float a, b, c;
    char *str_a, *str_b, *str_c;
    
    a = (rand() % 10) / 2.0 + 1.5;
    b = (rand() % 10) / 2.0 + 3.6;
    c = (rand() % 10) / 2.0 + 8.4;
    
    str_a = float_to_string(a);
    str_b = float_to_string(b);
    str_c = float_to_string(c);
    
    printf("The three random floats are: %s, %s and %s", str_a, str_b, str_c);
    
    free(str_a);
    free(str_b);
    free(str_c);
    
    return 0;
}

// Converts a float to a string
char *float_to_string(float f) {
    char *buf = (char *) malloc(sizeof(char) * 12);
    sprintf(buf, "%f", f);
    return buf;
}