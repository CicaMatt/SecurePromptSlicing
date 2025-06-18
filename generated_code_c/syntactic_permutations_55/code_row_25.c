#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

void login()
{
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html><html><head>");
    printf("<title>Login Page</title></head>");
    printf("<body><center>");
    printf("<h1>Login Page</h1>");
    printf("Username: <input type='text' name='uname'>");
    printf("Password: <input type='password' name='pwd'>");
    printf("<button type='submit'>Login</button></center>");
    printf("</body></html>");
}

void do_login()
{
    char username[32];
    char password[32];
    strcpy(username, getenv("QUERY_STRING"));
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html><html><head>");
    printf("<title>Login Page</title></head>");
    printf("<body><center>");
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0)
    {
        printf("Hello, %s!<br>", username);
        printf("Welcome to admin page!<br>");
        printf("<a href='/logout'>Logout</a>");
    }
    else
    {
        printf("Invalid credentials!<br>");
        printf("<a href='/login'>Login again?</a>");
    }
    printf("</center></body></html>");
}

void index()
{
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html><html><head>");
    printf("<title>Index Page</title></head>");
    printf("<body><center>");
    printf("<h1>Welcome to the index page!</h1>");
    printf("</center></body></html>");
}

void logout()
{
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html><html><head>");
    printf("<title>Logout Page</title></head>");
    printf("<body><center>");
    printf("You are now logged out!<br>");
    printf("<a href='/'>Back to index page</a>");
    printf("</center></body></html>");
}

void admin_page()
{
    char username[32];
    strcpy(username, getenv("QUERY_STRING"));
    if (strcmp(username, "admin") == 0)
    {
        printf("Content-Type: text/html\n\n");
        printf("<!DOCTYPE html><html><head>");
        printf("<title>Admin Page</title></head>");
        printf("<body><center>");
        printf("Welcome, %s!<br>", username);
        printf("You are now logged in as admin!<br>");
        printf("<a href='/logout'>Logout</a>");
        printf("</center></body></html>");
    }
    else
    {
        printf("Content-Type: text/html\n\n");
        printf("<!DOCTYPE html><html><head>");
        printf("<title>Login Page</title></head>");
        printf("<body><center>");
        printf("Invalid credentials!<br>");
        printf("<a href='/login'>Login again?</a>");
        printf("</center></body></html>");
    }
}