#include<stdio.h>
#include<stdbool.h>
#include<string.h>

void login();
void do_login(char name[], char password[]);

int main()
{
    login();
}

void login()
{
    printf("<form action='/do_login' method='POST'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br><br>\n");
    printf("<input type='submit' value='Submit'>\n");
    printf("</form>");
}

void do_login(char username[], char password[])
{
    if(strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
        redirect_to_admin_page();
    else
        return;
}

void redirect_to_admin_page()
{
    printf("Location: /admin_page");
}