#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    float f1 = (float)rand()/(float)(RAND_MAX/10);
    char string[5];
    sprintf(string, "%f", f1);

    float f2 = (float)rand()/(float)(RAND_MAX/10);
    char string2[5];
    sprintf(string2, "%f", f2);

    float f3 = (float)rand()/(float)(RAND_MAX/10);
    char string3[5];
    sprintf(string3, "%f", f3);
}