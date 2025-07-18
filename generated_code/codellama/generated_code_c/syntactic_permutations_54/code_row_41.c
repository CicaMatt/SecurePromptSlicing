#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

// Login function
void login()
{
    char *html = "<html><head><title>Login</title></head><body>"
                 "<form method='POST' action='/do_login'>"
                 "Username:<input type='text' name='username'><br />"
                 "Password:<input type='password' name='password'><br />"
                 "<input type='submit' value='Login'>"
                 "</form></body></html>";

    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("%s", html);
}

// Do Login function
void do_login()
{
    char *username = getenv("QUERY_STRING");
    char *password = getenv("REMOTE_ADDR");

    // Check if the user is admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0)
    {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><head><title>Admin Page</title></head><body>"
               "<h1>Welcome Admin!</h1></body></html>");
    }
    else
    {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><head><title>Login</title></head><body>"
               "<h1>Invalid Login!</h1></body></html>");
    }
}