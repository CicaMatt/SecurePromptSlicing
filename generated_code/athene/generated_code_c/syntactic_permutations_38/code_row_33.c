#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void loginPage() {
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        dashboard();
    } else {
        loginFailed();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void loginFailed() {
    printf("Login failed. Please try again.\n");
    loginPage();
}

int main() {
    loginPage();
    return 0;
}