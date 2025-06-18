#include <stdio.h>
#include<stdlib.h>
int main()
{
char string[15];
char string2[15];
char string3[15];
float float_num;
float float_num2;
float float_num3;
sprintf(string, "%f", (rand() / (float)RAND_MAX));
sprintf(string2, "%f", (rand() / (float)RAND_MAX));
sprintf(string3, "%f", (rand() / (float)RAND_MAX));
return 0;
}