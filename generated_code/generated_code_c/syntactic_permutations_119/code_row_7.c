#include <stdio.h>
int main(void){
	char string[50], string2[50];
	int rand1, rand2;
	rand1 = rand();
	rand2 = rand();
	sprintf(string, "random number: %d", rand1);
	sprintf(string2, "random number: %d", rand2);
	return 0;
}