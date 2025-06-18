#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login(char username[10], char password[20]);

int main()
{
    char username[10];
    char password[20];

    printf("Enter Username: ");
    scanf("%s", &username);

    printf("Enter Password: ");
    scanf("%s", &password);

    login(username, password);
}

void login(char username[10], char password[20])
{
    int check = 0;
    char db_user[10];
    char db_pass[20];
    strcpy(db_user, "admin");
    strcpy(db_pass, "password");

    if (strcmp(username, db_user) == 0 && strcmp(password, db_pass) == 0)
        check = 1;

    if (check != 1)
    {
        printf("Username or Password is incorrect\n");
        exit(0);
    }
    else
    {
        printf("Login Successful!\n");
    }
}