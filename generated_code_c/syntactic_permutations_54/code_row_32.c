#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int login(void)
{
    printf("Content-type: text/html\n\n");
    printf("<!DOCTYPE html><html><body>");
    printf("<form action=\"/_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Submit\"></form></body></html>");
}

int do_login(void)
{
    char* username;
    char* password;
    int valid_user = 0;

    // check if user is authorized
    // ...
    
    if (valid_user == 1) {
        printf("Content-type: text/html\n\n");
        printf("<!DOCTYPE html><html><body>");
        printf("Login successful. <a href=\"/_page\">Click here</a> to access the page.</body></html>");
    } else {
        login();
    }
}