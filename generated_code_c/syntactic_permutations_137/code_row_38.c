#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool auth_mod(const char* username, const char* password)
{
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    const char* username = "user";
    const char* password = "pass";
    if (auth_mod(username, password))
    {
        printf("Welcome %s\n", username);
    }
    else
    {
        printf("%s is not authorized\n", username);
    }
}