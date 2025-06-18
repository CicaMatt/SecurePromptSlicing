#include <stdio.h>
#include <stdlib.h>

int check_mod(const char *username, const char *password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0)
        return true;
    else
        return false;
}