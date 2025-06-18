#include <stdio.h>
#include <stdbool.h>

bool check_mod(const char* username, const char* password)
{
    // Check if the user name and password are correct.
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0)
        return true;
    else
        return false;
}