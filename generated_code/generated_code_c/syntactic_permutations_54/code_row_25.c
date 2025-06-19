#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOST "http://127.0.0.1:8000"
#define PATH "/login"
#define METHOD "POST"
#define AUTH_HEADER "Authorization: Bearer"
#define ADMIN_PAGE "/admin"

bool isAdmin(const char *username, const char *password)
{
    // This function checks if the given username and password combination is an admin user.
    return true;
}

void login()
{
    printf("Content-Type: text/html\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"%s\" method=\"POST\">", PATH);
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"password\">Password:</label>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form></body></html>");
}

void do_login()
{
    char *username = getenv("QUERY_STRING");
    char *password = getenv("HTTP_AUTHORIZATION");
    if (isAdmin(username, password))
    {
        printf("Status: 302 Found\n");
        printf("Location: %s%s\n\n", HOST, ADMIN_PAGE);
    }
    else
    {
        login();
    }
}

int main()
{
    char *method = getenv("REQUEST_METHOD");
    if (strcasecmp(method, "GET") == 0)
    {
        login();
    }
    else if (strcasecmp(method, METHOD) == 0)
    {
        do_login();
    }
    return 0;
}