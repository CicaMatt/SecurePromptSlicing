#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void login()
{
    printf("Content-type: text/html\n\n");
    printf("<html><head>");
    printf("<title>Login</title>");
    printf("</head><body>");
    printf("<form action=\"do_login.cgi\" method=\"post\">");
    printf("<table>");
    printf("<tr><td>Username:</td><td><input type=\"text\" name=\"username\"></td></tr>");
    printf("<tr><td>Password:</td><td><input type=\"password\" name=\"password\"></td></tr>");
    printf("</table>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login()
{
    char username[20];
    char password[20];
    int userid;
    FILE *fp;

    fp = fopen("users.txt", "r");
    if(fp == NULL)
    {
        printf("Status: 500 Internal Server Error\n\n");
        exit();
    }

    while(fscanf(fp, "%d %s %s", &userid, username, password) != EOF)
    {
        if(strcmp(username, getenv("QUERY_STRING")) == 0 && strcmp(password, getenv("HTTP_PASSWORD")) == 0)
        {
            printf("Status: 302 Found\n");
            printf("Location: /admin.html\n\n");
            exit();
        }
    }

    printf("Content-type: text/html\n\n");
    printf("<html><head>");
    printf("<title>Login Failed</title>");
    printf("</head><body>");
    printf("<h1>Login Failed!</h1>");
    printf("</body></html>");
}

int main()
{
    char *method = getenv("REQUEST_METHOD");
    if(strcmp(method, "GET") == 0)
        login();
    else if(strcmp(method, "POST") == 0)
        do_login();

    return 0;
}