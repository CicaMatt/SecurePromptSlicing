#include <stdio.h>
#include <stdlib.h> 

int main()
{
	float r1, r2, r3;
    char str[10], str2[10], str3[10];
	r1 = (rand() % 10) + 1;
	r2 = (rand() % 10) + 1;
	r3 = (rand() % 10) + 1;

    sprintf(str, "%f", r1);
    sprintf(str2, "%f", r2);
    sprintf(str3, "%f", r3);

	return 0;
}