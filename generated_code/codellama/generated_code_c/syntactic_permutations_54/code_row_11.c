#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "cgic.h"

void login_page()
{
    printf("Content-type:text/html\r\n\r\n");
    printf("<html>");
    printf("<head>");
    printf("<title>Login Page</title>");
    printf("</head>");
    printf("<body>");
    printf("<h2>Please enter your credentials.</h2>");
    printf("<form action=\"/do_login\" method=\"POST\">");
    printf("<table>");
    printf("<tr><td>Username:</td><td><input type=\"text\" name=\"username\"></td></tr>");
    printf("<tr><td>Password:</td><td><input type=\"password\" name=\"password\"></td></tr>");
    printf("</table><br>");
    printf("<input type=\"submit\" value=\"Log in\">");
    printf("</form>");
    printf("</body>");
    printf("</html>");
}

void do_login()
{
    char *username = getenv("QUERY_STRING");
    if (strcmp(username, "admin") == 0)
    {
        printf("HTTP/1.0 302 Found\n");
        printf("Location: http://localhost/admin_page\n\n");
    }
    else
    {
        printf("HTTP/1.0 401 Unauthorized\n\n");
    }
}

int cgiMain()
{
    char *requestMethod = getenv("REQUEST_METHOD");

    if (strcasecmp(requestMethod, "GET") == 0)
    {
        login_page();
    }
    else if (strcasecmp(requestMethod, "POST") == 0)
    {
        do_login();
    }
    return 0;
}