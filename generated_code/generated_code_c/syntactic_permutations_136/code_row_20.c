#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *check_user(username, password)
{
    char *user = "admin";
    char *pass = "1234567890";
    if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
        return "true";
    } else {
        return NULL;
    }
}

int main()
{
    char *user = getenv("QUERY_STRING");
    char *pass = getenv("HTTP_PASSWORD");
    if (check_user(user, pass) != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("Welcome %s", user);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("Invalid username or password");
    }

    return 0;
}