#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void loginPage();
void dashboardPage();

char storedUsername[MAX_USERNAME_LENGTH] = "admin";
char storedPassword[MAX_PASSWORD_LENGTH] = "password";

int main() {
    loginPage();
    return 0;
}

void loginPage() {
    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0) {
        dashboardPage();
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        loginPage();
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}