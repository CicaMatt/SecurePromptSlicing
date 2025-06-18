#include <stdio.h>
#include <stdbool.h>

int main()
{
    char *username = "user1";
    char *password = "pass1";
    bool session = true;
    check_mod(username, password, session);
}

bool auth_mod(char *username, char *password)
{
    if (strcmp(username, "moderator") == 0 && strcmp(password, "pass1") == 0)
        return true;
    else
        return false;
}