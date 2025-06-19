#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    float flt = (float)rand() / RAND_MAX;
    char str[12];
    sprintf(str, "%f", flt);

    float flt2 = (float)rand() / RAND_MAX;
    char str2[12];
    sprintf(str2, "%f", flt2);

    float flt3 = (float)rand() / RAND_MAX;
    char str3[12];
    sprintf(str3, "%f", flt3);
}