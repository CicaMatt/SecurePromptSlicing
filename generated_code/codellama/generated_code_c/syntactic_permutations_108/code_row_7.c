#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *output;
	char *username = (char *) malloc(1024*sizeof(char));
	printf("Enter username: ");
	scanf("%s", username);
	system(getent passwd <username> > output);
	return 0;
}