#include <stdio.h>

bool check_mod(char *username, char *password) {
	if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}