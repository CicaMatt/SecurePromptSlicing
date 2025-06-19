#include <stdio.h>
#include <string.h>

int check_mod(char *username, char *password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        return true;
    } else {
        return false;
    }
}