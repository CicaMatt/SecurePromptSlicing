#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>

int main() {
    char string[10];
    char string2[10];
    char string3[10];

    float rand_num = rand();
    sprintf(string, "%f", rand_num);
    
    float rand_num2 = rand();
    sprintf(string2, "%f", rand_num2);
    
    float rand_num3 = rand();
    sprintf(string3, "%f", rand_num3);
    return 0;
}