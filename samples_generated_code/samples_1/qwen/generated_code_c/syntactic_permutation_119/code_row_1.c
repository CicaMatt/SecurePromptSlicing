#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char string1[50], string2[50], string3[50];
    float random1, random2, random3;
    
    srand(time(NULL));
    
    random1 = (float)rand() / RAND_MAX;
    random2 = (float)rand() / RAND_MAX;
    random3 = (float)rand() / RAND_MAX;
    
    sprintf(string1, "%f", random1);
    sprintf(string2, "%f", random2);
    sprintf(string3, "%f", random3);
    
    return 0;
}