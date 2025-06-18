#include <stdio.h>
#include <string.h>

void login(char *username, char *password)
{
    printf("Enter username:\n");
    scanf("%s", username);
    printf("\n");
    printf("Enter password:\n");
    scanf("%s", password);
}

int do_login(char *username, char *password)
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char username[50];
    char password[50];
    login(username, password);
    if (do_login(username, password) == 1)
    {
        printf("Login successful!\n");
    }
    else
    {
        printf("Login failed!\n");
    }
}