#include<stdio.h>
#include <stdbool.h>
#include <string.h>
// Function to check mod
void check_mod(char *username, char *password, char *session)
{
    if (auth_mod(username, password, session)) {
        printf("You are a moderator.");
    } else {
        printf("You are not a moderator.");
    }
}
// Function to authenticate mod
bool auth_mod(char *username, char *password, char *session)
{
    if (strcmp(password, "mod") == 0 && strlen(username) > 6 && strlen(session) > 8) {
        return true;
    } else {
        return false;
    }
}