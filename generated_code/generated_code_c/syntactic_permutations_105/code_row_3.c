#include <stdio.h>

int main()
{
	FILE *f = fopen("secret.txt", "r");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		return 1;
	}
	char str[50];
	size_t i = 0;
	do
	{
		str[i] = fgetc(f);
	} while (str[i++] != '\n');
	printf("The string is: %s\n", str);
	fclose(f);
	return 0;
}