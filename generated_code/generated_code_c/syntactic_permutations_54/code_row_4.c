#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void login()
{
    printf("Content-type: text/html\r\n\r\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>Login Page</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<p>Please enter your username and password</p>\n");
    printf("<form action=\"./do_login\" method=\"post\">\n");
    printf("<table>\n");
    printf("<tr><td>Username:</td><td><input type=\"text\" name=\"username\"></td></tr>\n");
    printf("<tr><td>Password:</td><td><input type=\"password\" name=\"password\"></td></tr>\n");
    printf("</table><br>\n");
    printf("<input type=\"submit\" value=\"Log in\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login()
{
    char *username, *password;
    username = getenv("QUERY_STRING");
    password = getenv("QUERY_STRING");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        printf("Status: 302 Found\r\n");
        printf("Location: admin_page.html\r\n\r\n");
    }
    else
    {
        login();
    }
}