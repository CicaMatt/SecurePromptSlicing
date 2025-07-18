#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *username;
    printf("Enter Username : ");
    scanf("%s", &username);
    char *password;
    printf("\nEnter Password : ");
    scanf("%s", &password);
    if (strcmp(username, "John") == 0 && strcmp(password, "Doe") == 0) {
        //Login Successfull
        printf("Welcome to the Session Page");
    } else {
        //Invalid Login Credentials
        printf("Username or Password incorrect");
    }
}