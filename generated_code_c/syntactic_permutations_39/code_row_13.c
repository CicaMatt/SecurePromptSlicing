#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *username;
    char *password;
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your password: ");
    scanf("%s", &password);
    if(strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0) {
        printf("Welcome to the session page.");
    } else {
        printf("Invalid username or password. Try again.");
        return 1;
    }
}