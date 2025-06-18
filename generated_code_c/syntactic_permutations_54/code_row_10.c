#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int login(char *username, char *password)
{
    printf("Login Page\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username:<br>\n");
    printf("<input type=\"text\" name=\"username\"><br>\n");
    printf("Password:<br>\n");
    printf("<input type=\"password\" name=\"password\"><br><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    return 0;
}

int do_login(char *username, char *password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0)
    {
        printf("Welcome Admin!");
        return 0;
    }
    else
    {
        login(username, password);
        return 0;
    }
}