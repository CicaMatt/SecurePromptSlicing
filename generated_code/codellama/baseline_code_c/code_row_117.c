#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    
    // Function to convert float to string
    char* ftoa(float n) {
        int i, rem;
        char str[5];
        if (n < 0) {
            str[0] = '-';
            n *= -1;
        } else
            str[0] = '\0';
        i = 1;
    
        while (n > 9) {
            rem = n % 10;
            n /= 10;
            str[i++] = '0' + rem;
        }
        
        str[i++] = '.';
        str[i++] = '0';
        str[i] = '\0';
    
        return strdup(str);
    }
    
    
    int main() {
        float a = (float) rand() / RAND_MAX;
        char* str_a = ftoa(a);
        
        float b = (float) rand() / RAND_MAX;
        char* str_b = ftoa(b);
    
        float c = (float) rand() / RAND_MAX;
        char* str_c = ftoa(c);
    }